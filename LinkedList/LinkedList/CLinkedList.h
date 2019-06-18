#pragma once

#include <assert.h>
using namespace std;

template <typename T>
class CListNode
{
	template <typename T>
	friend class CLinkedList; //LinkedList���� private ���ٰ���

private:
	CListNode()		//������
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CListNode()	//�Ҹ���
	{		
	}
private:
	T m_Data;	//������
	CListNode<T>*	m_pNext;	//��������� �ּ�
	CListNode<T>*	m_pPrev;	//��������� �ּ�
};


template <typename T>
class CLinkedList
{
public:
	CLinkedList()	// ������
	{
		// �����Ҵ�
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		// �ʱ���´� Begin�� End�� ���� ����� ����
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CLinkedList()	// �Ҹ���
	{
		clear();
		delete	m_pBegin;
		delete	m_pEnd;
	}
private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

private:
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;

public:
	// End�� End ������� ���̿� ���ο� ��� �߰�
	void push_back(const T& data) //���۷��� : ��ü��ü�� ���� (�ӵ� ���)
	{
		//���ο� ��� ����
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		//End�� �������
		PNODE	pPrev = m_pEnd->m_pPrev;

		// End ������� -> ���ο���
		//		  	    <-  
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		// ���ο��� -> End ���
		//			  <-
		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		m_iSize++;
	}

	//Begin�� Begin ���� ��� ���̿� ���ο� ��� �߰�
	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data;
				
		// Begin�� �������
		PNODE	pNext = m_pBegin->m_pNext;

		// ���ο��� -> Begin �������
		//			 <-
		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		// Begin -> ���ο���
		//		 <-
		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;

		m_iSize++;
	}

	//Begin �������, ù��� ����
	void pop_front()
	{
		if (empty())
		{
			assert(false);
		}

		//���� ��带 ����
		PNODE	pDeleteNode = m_pBegin->m_pNext;

		//���� ����� ������带 ����
		PNODE	pNext = pDeleteNode->m_pNext;

		// Begin -> �������� �������
		//       <-
		pNext->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNext;

		//��带 ����
		delete	pDeleteNode;

		m_iSize--;
	}

	T front()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_pBegin->m_pNext->m_Data;
	}

	T back()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_pEnd->m_pPrev->m_Data;
	}

	// ��������带 ����
	void pop_back()
	{
		if (empty())
		{
			assert(false);
		}

		// ���� ���
		PNODE	pDeleteNode = m_pEnd->m_pPrev;

		// ���� ����� �������
		PNODE	pPrev = pDeleteNode->m_pPrev;

		// �������� ������� -> End
		//					   <-

		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		// ��带 �����
		delete pDeleteNode;

		m_iSize--;
	}

	void printList()
	{
		if (empty())
		{
			assert(false);
		}
		else
		{
			PNODE	pNode = m_pBegin->m_pNext;
			cout << "List [ ";
			while (pNode != m_pEnd)
			{
				cout << pNode->m_Data << " ";
				pNode = pNode->m_pNext;
			}
			cout << "]" << endl;
		}

	}

	// Begin�� End�� ������ ����� ����
	void clear()
	{
		PNODE	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			// �������� ������带 �޴´�
			PNODE	pNext = pNode->m_pNext;

			// �����带 �����
			delete	pNode;

			//���� ���� �̵��Ѵ�
			pNode = pNext;
		}

		m_iSize = 0;

		//Begin�� End�� ����
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}


	int size()	const
	{
		return m_iSize;
	}

	//�� ����Ʈ Ȯ��
	bool empty()	const
	{
		//������ ���̸� true, �����̸� false
		return m_iSize == 0;
	}
};
