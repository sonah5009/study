#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_ELEMENTS 101
char string[MAX_ELEMENTS][MAX_ELEMENTS];
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)
void randomString();
#define INT_MIN 0

typedef struct
{
  char *value;
  int key;
} element;


// 1. array

element heap_arr[MAX_ELEMENTS];
// key값에 따라 정렬
int size = -1;

void enqueue(char *value, int key)
{
  size++;
  heap_arr[size].value = value;
  heap_arr[size].key = key;
}

// 최상단의 element(key)값 확인
int check()
{
  int highestkey = INT_MIN;
  int idx = -1;
  // 가장 높은 key를 가진 element 확인
  for (int i = 0; i <= size; i++)
  {
    // key값 갱신
    if (highestkey < heap_arr[i].key )
    {
      highestkey = heap_arr[i].key;
      idx = i;
    }
  }
  // element 어딨는지 index 값 반환
  return idx;
}
// 최상단 값 삭제 size--함으로써
void dequeue()
{
  // 가장 높은 key값이 있는 element 위치
  int idx = check();

 // 한 인덱스 이전으로 이동. idx값 부터 size의 끝까지
  for (int i = idx; i < size; i++)
  {
    heap_arr[i] = heap_arr[i + 1];
  }
  size--;
}

// 2. linked list

typedef struct listNode *listPointer;
typedef struct listNode
{
  element data;
  listPointer link;
} listNode;

void insert_linked(listPointer first, element data_)
{
  listPointer temp = (listPointer)malloc(sizeof(*temp));
  listPointer left;
  left = first;
  temp->data = data_;
  // 들어온 key값 보다 작은 노드 찾기
  
  while(left->link && temp->data.key < left->link->data.key)
  {
    left = left->link;
  }
  
  temp->link = left->link;
  left->link = temp;
}

void remove_linked(listPointer first)
{
  // 더미노드의 다음 노드가 NULL이면 종료
  if(first->link == NULL) return;
  listPointer temp = first;
  temp = first->link;
  first->link = first->link->link;
  
  printf("%d ", temp->data.key);

  free(temp);
  temp = NULL;
}


// 3. max heap

element heap[MAX_ELEMENTS];
int n = 0;

void push(element item)
{
  int i;
  if (HEAP_FULL(n))
  {
    printf("The heap is full");
    exit(1);
  }

  i = ++n;
  // 자식 index/2의 정수 몫은 부모 index값임
  // 들어오려는 값이 부모보다 크면 실행
  while ((i != 1) && (item.key > heap[i / 2].key))
  {
    heap[i] = heap[i / 2];
    i /= 2;
  }

  heap[i] = item;
}

element pop()
{
    int parent, child;
    element item, temp;

    if (HEAP_EMPTY(n)) {
        fprintf(stderr, "The heap is empty");
        exit(1);
    }
    // 가장 큰 키 저장
    item = heap[1];
    // 마지막 노드 사용하여 힙 재구성
    temp = heap[n--];
    parent = 1;
    child = 2;

    while (child <= n) {
        if ((child < n) && (heap[child].key < heap[child + 1].key)) {
            child++;
        }

        if (temp.key >= heap[child].key) {
            break;
        }

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }

    heap[parent] = temp;

    return item;
}


// 4. binary search
typedef struct node *treePointer;
typedef struct node
{
  element data;
  treePointer leftChild;
  treePointer rightChild;
} node;


// parameter로 들어오는 key값이 기존 key값보다 작으면 leftchild, 크면 right child로 들어간다
treePointer modifiedSearch(treePointer tree, int k)
{
  if (!tree)
    return NULL;

  while (tree)
  {
    if (k == tree->data.key)
      return NULL;
    else if (k < tree->data.key)
    {
      if (tree->leftChild)
        tree = tree->leftChild;
      else
        break;
    }
    else
    {
      if (tree->rightChild)
        tree = tree->rightChild;
      else
        break;
    }
  }
  return tree;
}

// key값에 따라 자리를 찾아서 삽입
void insert(treePointer *node, int k, char *v)
{
  treePointer ptr, temp = modifiedSearch(*node, k);
  // case 1: temp가 null이 아닐 떄
  // case 2: temp가 null이고, !(*node)가 참일 때
  // (*node): 노드에 아무 것도 없음
  if (temp || !(*node))
  {
    ptr = (treePointer)malloc(sizeof(*ptr));
    ptr->data.key = k;
    ptr->data.value = v;
    ptr->leftChild = ptr->rightChild = NULL;

    if (*node)
    {
      if (k < temp->data.key)
        temp->leftChild = ptr;
      else
        temp->rightChild = ptr;
    }
    else
      *node = ptr;
  }
}

void delete_bst(treePointer node)
{
  // 아무 노드도 없을 때 종료
  if(!(node)) return;
  treePointer temp = node;
  if(temp->rightChild)
  {
    // case0: right node -> right node 있을 때까지만 재귀. 즉 else에는 직속 child가 right노드가 하나만 있거나 없거나임
    if(temp->rightChild->rightChild)
      delete_bst(temp->rightChild);

    else if(temp->rightChild->leftChild){
    // case1: right node->left node 있을 때
      printf("%d ", node->rightChild->data.key);
      temp = node->rightChild;
      node->rightChild = node->rightChild->leftChild;
      free(temp);
      temp =NULL;
    }
    else
    {
    // case2: right node만 있을 때
      printf("%d ", node->rightChild->data.key);
      free(node->rightChild);
      node->rightChild = NULL;
    }
  }
  else if(temp->leftChild)
  {
  // case3: leftnode만 있을 때
    if(temp->leftChild->leftChild==NULL && temp->leftChild->rightChild==NULL)
    {
      // case3: 노드 하나일 때
      printf("%d ", node->data.key);
      node->data = node->leftChild->data;
      free(node->leftChild);
      node->leftChild = NULL;
    }
    else
    {
      // case4: left child, leftchild의 자식이 있을 때
      printf("%d ", node->data.key);
      node->data = node->leftChild->data;
      temp = node->leftChild;
      if(node->leftChild->rightChild)
      {
        node->rightChild = (treePointer)malloc(sizeof(*node));
        node->rightChild = node->leftChild->rightChild;
      }
      if(node->leftChild->leftChild)
      {
        node->leftChild = node->leftChild->leftChild;
      }
      free(temp);
      temp = NULL;
    }
  }
  else
  {
    // case5: 노드 하나일 때
      printf("%d ", node->data.key);
      free(node);
      node = NULL;
  }
}

// ===========================================================================

// 100 byte string 생성
void randomString()
{
  char ch;

  srand(time(0));
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    for (int j = 0; j < MAX_ELEMENTS - 1; j++)
    {
      ch = rand() % 26 + 'a';
      string[i][j] = ch;
    }
    string[i][MAX_ELEMENTS - 1] = '\0';
  }
}

// main
int main(void)
{
  randomString();
  // 1-100 key값 생성
  int keys[MAX_ELEMENTS];
    keys[0] = 0;
  srand(time(0));
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    keys[i] = (rand() % MAX_ELEMENTS);
    for (int j = 0; j < i; j++)
    {
      if (keys[i] == keys[j])
        i--;
    }
  }

  clock_t start;
  clock_t end;

 // 1. array
  printf("[array]============================================================\n");
  start = clock();
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    // heap에 넣기
    enqueue(string[i], keys[i]);
  }
  // heap[]에 있는 걸 sort해서 sort_arr[]에 저장
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    int idx = check();
    printf("%d ", heap_arr[idx].key);
    dequeue();
  }
  end = clock();
  printf("\n");
  printf("소요 시간: %lf\n\n", (double)(end - start));
  
  // 2. linked list
  printf("[linked list]============================================================\n");
  // 더미 노드 생성
  listPointer x = (listPointer)malloc(sizeof(*x));
  element temp;

  start = clock();
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    temp.key = keys[i];
    temp.value = string[i];
    insert_linked(x, temp);
  }
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    remove_linked(x);
  }
  end = clock();
  printf("\n");
  printf("소요 시간: %lf\n\n", (double)(end - start));


// 3. max heap
  element temp_heap;
  printf("[max heap]============================================================\n");

  start = clock();
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    temp_heap.key = keys[i];
    temp_heap.value = string[i];
    push(temp_heap);
  }
  for (int i = 1; i < MAX_ELEMENTS; i++)
    printf("%d ", pop().key);
  end = clock();
  printf("\n");
  printf("소요 시간: %lf\n\n", (double)(end - start));

  // 4. binary search
  printf("[binary search]============================================================\n");
  treePointer root = NULL;

  start = clock();
  for (int i = 1; i < MAX_ELEMENTS; i++)
  {
    insert(&root, keys[i], string[i]);
  }

  for (int i = MAX_ELEMENTS-1; i >=1; i--) {
    delete_bst(root);
  }
  end = clock();
  printf("\n");
  printf("소요 시간: %lf\n\n", (double)(end - start));

  return 0;
}
