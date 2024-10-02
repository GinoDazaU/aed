
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        return new TreeNode(10);
    }

    int arrayInOrder(TreeNode* root) {
        if(root->left != nullptr) {
            inOrder(root->left);
        }
        cout << root->val << " ";
        if(root->right != nullptr) {
            inOrder(root->right);
        }
        if(root->left == nullptr && root->right == nullptr) {
            return 0;
        }
    }

    void inOrder(TreeNode* root) {
        if(root == nullptr) return;
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
};

int main() {

    TreeNode tree_node(1);
    tree_node.right = new TreeNode(2);
    tree_node.right->right = new TreeNode(3);
    tree_node.right->right->right = new TreeNode(4);

    TreeNode tree_node1(10);
    tree_node1.left = new TreeNode(8);
    tree_node1.right = new TreeNode(12);
    tree_node1.left->left = new TreeNode(7);
    tree_node1.left->right = new TreeNode(9);
    tree_node1.right->left = new TreeNode(11);

    Solution sol;
    sol.inOrder(&tree_node1);


    return 0;
}