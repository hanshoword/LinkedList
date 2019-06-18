#pragma once

#include <assert.h>
using namespace std;

template <typename T>
class CListNode
{
	template <typename T>
	friend class CLinkedList; //LinkedList에서 private 접근가능

private:
	CListNode()		//생성자
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CListNode()	//소멸자
	{		
	}
private:
	T m_Data;	//데이터
	CListNode<T>*	m_pNext;	//다음노드의 주소
	CListNode<T>*	m_pPrev;	//이전노드의 주소
};


template <typename T>
class CLinkedList
{
public:
	CLinkedList()	// 생성자
	{
		// 동적할당
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		// 초기상태는 Begin과 End가 서로 연결된 상태
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CLinkedList()	// 소멸자
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
	// End와 End 이전노드 사이에 새로운 노드 추가
	void push_back(const T& data) //레퍼런스 : 객체자체를 참조 (속도 향상)
	{
		//새로운 노드 생성
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		//End의 이전노드
		PNODE	pPrev = m_pEnd->m_pPrev;

		// End 이전노드 -> 새로운노드
		//		  	    <-  
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		// 새로운노드 -> End 노드
		//			  <-
		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		m_iSize++;
	}

	//Begin과 Begin 다음 노드 사이에 새로운 노드 추가
	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data;
				
		// Begin의 다음노드
		PNODE	pNext = m_pBegin->m_pNext;

		// 새로운노드 -> Begin 다음노드
		//			 <-
		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		// Begin -> 새로운노드
		//		 <-
		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;

		m_iSize++;
	}

	//Begin 다음노드, 첫노드 삭제
	void pop_front()
	{
		if (empty())
		{
			assert(false);
		}

		//지울 노드를 얻어옴
		PNODE	pDeleteNode = m_pBegin->m_pNext;

		//지울 노드의 다음노드를 얻어옴
		PNODE	pNext = pDeleteNode->m_pNext;

		// Begin -> 지울노드의 다음노드
		//       <-
		pNext->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNext;

		//노드를 삭제
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

	// 마지막노드를 삭제
	void pop_back()
	{
		if (empty())
		{
			assert(false);
		}

		// 지울 노드
		PNODE	pDeleteNode = m_pEnd->m_pPrev;

		// 지울 노드의 이전노드
		PNODE	pPrev = pDeleteNode->m_pPrev;

		// 지울노드의 이전노드 -> End
		//					   <-

		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		// 노드를 지운다
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

	// Begin과 End를 제외한 노드의 삭제
	void clear()
	{
		PNODE	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			// 현재노드의 다음노드를 받는다
			PNODE	pNext = pNode->m_pNext;

			// 현재노드를 지운다
			delete	pNode;

			//다음 노드로 이동한다
			pNode = pNext;
		}

		m_iSize = 0;

		//Begin과 End를 연결
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}


	int size()	const
	{
		return m_iSize;
	}

	//빈 리스트 확인
	bool empty()	const
	{
		//조건이 참이면 true, 거짓이면 false
		return m_iSize == 0;
	}
};
