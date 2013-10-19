#include <iostream>
#include <queue>
#include <stack>

using namespace std;


struct BinaryTreeNode
{
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

stack<int> path;

BinaryTreeNode *ConstructCore(int *startPreorder, int *endPreorder,
							  int *startInorder, int *endInorder)
{
	BinaryTreeNode *root = new BinaryTreeNode;
	root->value = startPreorder[0];

	// 在中序遍历中找到根节点的值
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != root->value)
	{
		++rootInorder;
	}
	if (rootInorder == endInorder && *rootInorder != root->value)
	{
		throw std::exception();
	}

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + leftLength;
	if (leftLength > 0)
	{
		root->left = ConstructCore(startPreorder+1, leftPreorderEnd, startInorder, rootInorder-1);
	}
	else
	{
		root->left = NULL;
	}

	if (rootInorder != endInorder)
	{
		root->right = ConstructCore(leftPreorderEnd+1, endPreorder, rootInorder+1, endInorder);
	}
	else 
	{
		root->right = NULL;
	}

	return root;
}


BinaryTreeNode *Construct(int *preorder, int *inorder, int length)
{
	if (preorder == NULL || inorder == NULL || length <= 0)
	{
		return NULL;
	}

	return ConstructCore(preorder, preorder+length-1, inorder, inorder+length-1);
}


BinaryTreeNode *Construct(int *nodeArray, int length)
{
    if(nodeArray == NULL || length == 0)
        return NULL;

    queue<BinaryTreeNode *>nodeQueue;
    BinaryTreeNode *head = new BinaryTreeNode;
    head->value = nodeArray[0];
    nodeQueue.push(head);
    BinaryTreeNode *p = NULL;
    int pos = 1;
    while(!nodeQueue.empty())
    {
        if(pos+1 >= length)
        {
            cout << "input error" << endl;
            return NULL;
        }

        p = nodeQueue.front();
        nodeQueue.pop();
        if(nodeArray[pos] > 0)
        {
            p->left = new BinaryTreeNode;
            p->left->value = nodeArray[pos];
            nodeQueue.push(p->left);
        }
        else
        {
            p->left = NULL;
        }

        if(nodeArray[pos+1] > 0)
        {
            p->right = new BinaryTreeNode;
            p->right->value = nodeArray[pos+1];
            nodeQueue.push(p->right);
        }
        else
        {
            p->right = NULL;
        }
        pos += 2;
    }

    return head;
}


void LevelOrder(BinaryTreeNode *root)
{
    if (root == NULL) {
        return;
    }

	queue<BinaryTreeNode *> nodeQueue;
	nodeQueue.push(root);
	BinaryTreeNode *p = NULL;
	while (!nodeQueue.empty())
	{
		p = nodeQueue.front();
		nodeQueue.pop();

		cout << p->value << "\t";
		if (p->left)
		{
			nodeQueue.push(p->left);
		}
		if (p->right)
		{
			nodeQueue.push(p->right);
		}
	}
    cout << endl;
}


void postOrderNonRecursive(BinaryTreeNode *root)
{
  if(root == NULL)
  {
    return;
  }

  stack<BinaryTreeNode *> s;
  s.push(root);
  BinaryTreeNode *prev = NULL;
  while(!s.empty())
  {
    BinaryTreeNode *pNode = s.top();
    if(pNode->left != NULL && prev != pNode->left && (prev != pNode->right || prev == NULL))
    {
      s.push(pNode->left);
    }
    else if(pNode->right != NULL && prev != pNode->right)
    {
      s.push(pNode->right);
    }
    else
    {
      prev = pNode;
      cout << pNode->value << "  ";
      s.pop();
    }
  }
  cout << endl;
}


BinaryTreeNode *mirror(BinaryTreeNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    BinaryTreeNode *pRight = head->right;
    head->right = mirror(head->left);
    head->left = mirror(pRight);

    return head;
}


bool HasRootSubTree(BinaryTreeNode *rootA, BinaryTreeNode *rootB)
{
    if (rootB == NULL) {
        return true;
    }
    if (rootA == NULL)
    {
        return false;
    }
    else
    {
        if (rootA->value == rootB->value) {
            return (HasRootSubTree(rootA->left, rootB->left) && HasRootSubTree(rootA->right, rootB->right));
        }
        else
        {
            return false;
        }
    }
}

bool HasSubTree(BinaryTreeNode *rootA, BinaryTreeNode *rootB)
{
    if (rootA == NULL || rootB == NULL) {
        return false;
    }

    queue<BinaryTreeNode *> nodeQueue;
    nodeQueue.push(rootA);
    BinaryTreeNode *p = NULL;
    while(!nodeQueue.empty())
    {
        p = nodeQueue.front();
        nodeQueue.pop();

        if (HasRootSubTree(p, rootB)) {
            return true;
        }
        if (p->left) {
            nodeQueue.push(p->left);
        }
        if(p->right)
        {
            nodeQueue.push(p->right);
        }

    }
    return false;
}


bool FindPath(BinaryTreeNode *root, int sum)
{
    if (root == NULL || sum <= 0) {
        return false;
    }

    if (root->left == NULL && root->right == NULL) {
        if (root->value == sum) {
            path.push(root->value);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool leftresult = false;
    if (root->left) {
        leftresult = FindPath(root->left, sum-root->value);
    }

    bool rightresult = false;
    if (root->right) {
        rightresult = FindPath(root->right, sum-root->value);
    }

    if (leftresult || rightresult) {
        if (leftresult) {
            path.push(root->value);
        }
        if (rightresult) {
            path.push(root->value);
        }
        return true;
    }
    else {
        return false;
    }
}


void ConverToLinkList(BinaryTreeNode *root, BinaryTreeNode **head, BinaryTreeNode **tail)
{
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        *head = root;
        *tail = root;
        return;
    }
    BinaryTreeNode *leftHead = NULL, *leftTail = NULL;
    if (root->left) {
        ConverToLinkList(root->left, &leftHead, &leftTail);
    }

    BinaryTreeNode *rightHead = NULL, *rightTail = NULL;
    if (root->right) {
        ConverToLinkList(root->right, &rightHead, &rightTail);
    }

    root->left = leftTail;
    leftTail->right = root;
    root->right = rightHead;
    rightHead->left = root;
    
    *head = leftHead;
    *tail = rightTail;
}


int main()
{
	int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};
    int nodeArrayA[] = {8, 8, 7, 9, 2, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0};
    int nodeArrayB[] = {8, 9, 2, 0, 0, 4, 7, 0, 0, 0, 0};
    int array[] = {1, 2, 3, 4, 5, 6, 7, 0, 0, 8, 0, 0, 9, 0, 0, 0, 0, 0, 0};
    int bstArray[] = {10, 6, 14, 4, 8, 12, 16, 0, 0, 0, 0, 0, 0, 0, 0};

    BinaryTreeNode *root = Construct(array, sizeof(array)/sizeof(int));
	BinaryTreeNode *rootA = Construct(nodeArrayA, sizeof(nodeArrayA)/sizeof(int));
    BinaryTreeNode *rootB = Construct(nodeArrayB, sizeof(nodeArrayB)/sizeof(int));
    BinaryTreeNode *bstRoot = Construct(bstArray, sizeof(bstArray)/sizeof(int));
    
    LevelOrder(bstRoot);
    postOrderNonRecursive(root);
    /*
    BinaryTreeNode *head = NULL, *tail = NULL;
    ConverToLinkList(bstRoot, &head, &tail);
    BinaryTreeNode *p = tail;
    while(p!=NULL)
    {
        cout << p->value << endl;
        p = p->left;
    }
    */
//    bool result = HasSubTree(rootA, rootB);
//    cout << result << endl;
	return 0;
}
