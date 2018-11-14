#include<iostream>
#include<string>


#include "DisJointSet.h"
#include "DisJointSetImpl.h"

using namespace std;

template<typename T> DisJointSet<T>::DisJointSet()
{

}

template<typename T> bool DisJointSet<T>::makeSet(const T& input)
{
	{
	shared_lock<shared_mutex> readLock(m_mutex);
	if(m_map.find(input) != m_map.end())
		return(false);
	}

	unique_lock<shared_mutex> exclusiveLock(m_mutex);
	shared_ptr<Node> m_ptr = make_shared<Node>(input);
	m_ptr->m_parent = m_ptr;
	m_map[input] = m_ptr;
	return(true);
}

template<typename T> shared_ptr<typename DisJointSet<T>::Node> DisJointSet<T>::getParent(const shared_ptr<typename DisJointSet<T>::Node>& input)
{
	shared_ptr<Node> current = input;
	shared_ptr<Node> parent = input->m_parent;

	while(current != parent)
	{
		current=current->m_parent;
		parent=parent->m_parent;
	}
	return(parent);
}

template<typename T> bool DisJointSet<T>::makeUnion(const T& input1, const T& input2)
{
	{
		shared_lock<shared_mutex> readLock(m_mutex);
		if(m_map.find(input1) == m_map.end() || m_map.find(input2) == m_map.end())
			return(false);
	}

	unique_lock<shared_mutex> exclusiveLock(m_mutex);
	shared_ptr<Node> node1 = m_map.find(input1)->second;
	shared_ptr<Node> node2 = m_map.find(input2)->second;

	shared_ptr<Node> parent1 = getParent(node1);
	shared_ptr<Node> parent2 = getParent(node2);

	if(parent1 == parent2)
		return(false);

	if(parent1->m_rank >= parent2->m_rank)
	{
		parent1->m_rank = (parent1->m_rank == parent2->m_rank) ? parent1->m_rank + 1 : parent1->m_rank;
		parent2->m_parent = parent1;
	}
	else
		parent1->m_parent = parent2;

	return(true);
}

template<typename T> T DisJointSet<T>::findSet(const T& input)
{
	shared_lock<shared_mutex> readLock(m_mutex);
	const auto& item = m_map.find(input);
	T result;
	if(item == m_map.end())
		return(result);
	else
		return(getParent(item->second)->m_data);
}

template<typename T> DisJointSet<T>::~DisJointSet()
{
	// For nodes pointing to themselves as parent in shared_ptr it can cause memory leak. reset them before cleaning the map. else memory leak will occur!
	for(auto& iter : m_map)
	{
		if(iter.second->m_parent == iter.second)
			iter.second->m_parent=nullptr;
	}
	m_map.clear();
}











