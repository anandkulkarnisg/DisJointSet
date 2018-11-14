#include<iostream>
#include<string>
#include<memory>
#include<unordered_map>

#ifndef DisJointSet_H
#define DisJointSet_H

template<typename T> class DisJointSet
{
	private:
		struct Node
		{
			T m_data;
			int m_rank;
			std::shared_ptr<Node> m_parent;

			Node(const T& input=0)
			{
				m_data=input;
				m_rank=0;
				m_parent=nullptr;
			}

			~Node() { }
		};

	std::unordered_map<T, std::shared_ptr<Node> > m_map;
	std::shared_ptr<Node> getParent(const std::shared_ptr<Node>&);

	public:
		DisJointSet();
		bool makeSet(const T&);
		bool makeUnion(const T&, const T&);
		T findSet(const T&);
		void dumpContents();
		~DisJointSet();
};

#endif
