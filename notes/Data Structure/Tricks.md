# Data Structure

## Binary Search Tree (BST)

- Inorder Traversal can yield a sorted array; this property can be used to check:

  - if the tree is validated (note that some trees allow duplicates while others disallow)
  - if not validated, which node has gone wrong
    - Turn the tree into an array of values, check if the array is sorted and search the tree for the wrong value
    - Can be optimized by turning the tree into an array of *TreeNode* pointers, writing a functor to compare the *TreeNode* values and locating the *Treenode* without having to search the tree for the specified value

- For iterative method of Inorder, Preorder and Postorder Traversal, we can use *Stack*, the code using C++ is as follows. Some similarities for these three kinds of traversal: the first step is to go to the leftmost node; then it is all about poping the top out of the stack, doing some operations and pushing some other things back if necessary

  - Inorder Traversal: left -> node -> right

    ```c++
    vector<int> inorderTraversal(TreeNode* root) {
    				stack<TreeNode*> Stack;
        		vector<int> nums;
        		//get to the leftmost node
            while (root != nullptr) {
                Stack.push(root);
                root = root->left;
            }
            
            while (!Stack.empty()) {
                TreeNode* currentNode = Stack.top();
                Stack.pop();
                // Inorder: if the node's leftChilds are consumed, then it comes to the node itself
                nums.push_back(currentNode->val);
                // Come to the right childs of the node
                currentNode = currentNode->right;
                while (currentNode != nullptr) {
                    Stack.push(currentNode);
                    currentNode = currentNode->left;
                }
            }
            
            return nums;
        }
    ```

  - Preorder Traversal: node->left->right, so each node's value is stored in the vector before putting onto the stack

    ```c++
    vector<int> preOrderTraversal(TreeNode* root){
      			stack<TreeNode*> Stack;
        		vector<int> nums;
      			//comes to the leftmost node
            while (root) {
                Stack.push(root);
                //preorder traversal, the current node comes first
                nums.push_back(root->val);
                root = root->left;
            }
            
            while(!Stack.empty()){
                //current node's value is already stored in the nums vector
                TreeNode* current = Stack.top();
                Stack.pop();
                current = current->right;
                while (current) {
                    //preorder
                    nums.push_back(current->val);
                    Stack.push(current);
                    current = current->left;
                }
            }
            
            return nums;
        }
    ```
  
  - Postorder: left -> right -> node
  
    ```c++
    vector<int> postOrderTraversal(TreeNode* root){
      			stack<TreeNode*> Stack;
        		vector<int> nums;
      			//go to the leftmost node; for each node in the stack, the left child will come before the node
            while (root) {
                Stack.push(root);
                root = root->left;
            }
            
            while (!Stack.empty()) {
                TreeNode* current = Stack.top();
                //if there is right child
                if (current->right) {
                    current = current->right;
                    //go to the leftmost of the right child
                    while (current) {
                        Stack.push(current);
                        current = current->left;
                    }
                }
                //else, we can add the node to the output;
                //also note that if the current node if the right child of the previous node, we can add the chain to the output as well
                else{
                    Stack.pop();
                    if (Stack.empty()) nums.push_back(current->val);
                    else{
                        TreeNode* next = Stack.top();
                        nums.push_back(current->val);
                        while (next->right == current) {
                            current = next;
                            nums.push_back(current->val);
                            Stack.pop();
                            if (Stack.empty()) break;
                            else next = Stack.top();
                        }
                    }
                }
            }
            
            return nums;
        }
    ```



# LInked list

### Find the node in the middle of the linked list

We can do so by using two pointer `slow_ptr` and `fast_ptr`, where the `slow_ptr` travels one node at a time and `fast_ptr` travels two nodes at a time. By the time that the `fast_ptr` reaches the end of the linked list, the `slow_ptr` will point towards the middle of the linked list. This method saves complexity and space. *(Leetcode #109)*



## Operations

### Find the number that exists once in an array whereas other numbers exist twice

The fastest way to do this is to do *XOR* operation on all the numbers in the array. Since a number *XOR* itself will yield zero, the result will be exactly the number we are looking for.

**However, what if there are two numbers that exist once in the array?**

In this case, we can still do *XOR* on all the elements. Then, we can divide the array into two subarrays by the criteria that elements from one subarray has bit 1 while those from the other has bit 0 on digit where the *XOR* result bit is 1 (which means that the two numbers has different bits on this digit). Then doing *XOR* on two diferent subarray will yield the two numbers we are looking for.

