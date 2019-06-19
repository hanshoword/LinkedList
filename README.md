## LinkedList

### CLinkedList.h 헤더파일
#### 에러처리 헤더파일 및 std 포함
```c
#include <assert.h>
using namespace std;
```

#### ListNode Class
```c
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
```

template <typename T>를 이용해 여러 자료형들을 충족 할 수 있습니다.

friend class는 CLinkedList로 해당 클래스에서 private 변수에 접근 할 수 있습니다.
 
이 LinkedList는 이전노드의주소와 다음노드의주소 previous와 next가 존재하는 Double LinkedList입니다.

생성자에서 주소값들을 nullptr로 초기화를 시켜줍니다.

멤버변수는 T형 데이터, 다음노드의 주소, 이전노드의 주소이며 주소를 저장해야하므로 CListNode<T>*형으로 이루어져있습니다.

#### CLinkedList Class

```c
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
```

리스트의 초기 형태는 Begin노드와 End노드가 연결된 형태입니다.

멤버변수는 Begin노드, End노드, List의 현재 크기를 나타내는 Size변수가 있습니다.

typedef로 CListNode<T>를 NODE로, CListNode<T>*를 PNODE로 편하게 사용하도록 정의합니다.

생성자에서는 Begin과 End는 항상 존재해야하므로 동적할당으로 초기화하고, 

Begin->next = End, End->prev = Begin으로 서로 연결시킵니다.

소멸자에서는 clear함수를 통해 추가된 노드를 삭제시키고, 마지막 Begin과 End를 delete합니다.

이제부터 클래스의 함수들 각각에 대해 설명해보겠습니다.

##### push_back 함수
```c
public:
  void push_back(const T& data) //레퍼런스 : 객체자체를 참조 (속도 향상)
	{
		//새로운 노드 생성
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		//End의 이전노드
		PNODE	pPrev = m_pEnd->m_pPrev;

		// End 이전노드 -> 새로운노드
		// End 이전노드 <-  새로운노드
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		// 새로운노드 -> End 노드
		// 새로운노드 <- End 노드
    pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		m_iSize++;
	}
```

End 앞에 노드를 삽입하는 함수입니다.

새로운 노드를 만들고 데이터를 넣습니다.

End의 이전노드를 받아와서, 

End의 이전노드의 다음노드는 새로운노드가 되고, 

새로운노드의 이전노드는 End의 이전노드로 설정합니다.

새로운노드의 다음은 End노드가 되고,

End노드의 이전은 새로운노드가 되어, End이전노드와 End사이에 삽입이 완료됩니다.

마지막으로 리스트 사이즈를 1 늘립니다.

##### push front 함수
```c
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
```

Begin 다음에 노드를 삽입합니다.

새로운노드를 만들고 데이터를 넣습니다.

Begin의 다음노드를 받아와,

Begin의 다음노드의 이전은 새로운노드로,

새로운 노드의 다음노드를 Begin의 다음노드로 설정합니다.

그리고 Begin의 다음을 새로운노드로,

새로운 노드의 이전을 Begin으로 설정하며 삽입을 완료합니다.

마지막으로 사이즈를 1증가시킵니다.

##### bool empty 함수
```c
//빈 리스트 확인
	bool empty()	const
	{
		//조건이 참이면 true, 거짓이면 false
		return m_iSize == 0;
	}
```

사이즈가 0이면 true, 아니면 false를 반환합니다.

##### size 함수

```c
	int size()	const
	{
		return m_iSize;
	}
```
리스트 사이즈를 반환합니다.



##### pop_back 
```c
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
```

empty함수를 통해 리스트가 비어있으면 assert로 에러처리를 합니다.

지울 노드(End의 이전노드)를 받아옵니다 

End의 이전 노드의 이전노드(pPrev)를 받아옵니다. (End의 이전노드의 이전노드와 End를 연결시켜야하므로)

pPrev의 다음을 End로, End의 이전을 pPrev로 하여 서로 연결합니다.
 
지울 노드를 delete하고 사이즈를 1줄이며 마칩니다.

##### pop front 함수 : Begin의 다음노드를 삭제
```c
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
```

먼저 빈 리스트이면 assert로 처리합니다.

지울노드는 Begin의 next노드입니다.

Begin의 next의 next노드와 Begin을 이어줘야하므로 Begin의 다음다음노드(pNext)를 받아옵니다.

pNext의 이전노드는 Begin으로 하고, Begin의 다음노드는 pNext로 하여 연결합니다.

그리고 지울노드를 delete 한 후 사이즈를 1 내립니다.

##### T front, T back 함수 : 처음노드와 마지막노드의 데이터를 반환하는 함수

```c
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
```

empty함수를 통해 빈 리스트이면 에러처리를 하고,

처음 노드는 Begin의 next, 마지막노드는 End의 prev의 데이터를 반환합니다.

```c
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
```

처음노드(Begin의 다음노드)를 가져옵니다.

현재노드의 다음노드를 받아놓고, 현재 노드를 지운 후, 받아놓은 다음노드를 현재노드로 바꿉니다.

이 과정인 현재노드가 다음노드로 이동 한 후 End가 아닐 때 까지 반복합니다.

그러면 End의 이전노드는 삭제되고 다음노드로 이동하게되면 End가 되므로 반복문에서 나옵니다.

노드가 모두 삭제되었으므로 Size = 0으로 바꾸고, Begin과 End를 연결합니다.


##### printList 함수 : 연결된 리스트를 출력하는 함수

```c
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
```

리스트가 비었으면 assert로 에러처리합니다.

현재노드를 Begin의 다음노드부터 시작합니다.

현재노드가 End노드가 아니면, 해당 노드의 데이터를 출력하고 다음노드로 이동합니다.


##### 결과

<img width="1500" src = "https://user-images.githubusercontent.com/47768726/59759883-ffd9f000-92cb-11e9-8fce-fa104171442d.JPG">
