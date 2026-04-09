// NOT ACTUALLY DP, JUST USING THE CONCEPT OF BREAKING INTO SUBPROBLEMS

/*
Leetcode 543. Diameter of Binary Tree
Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

- Fixed template: 
    base cond
    Hypothesis
    Induction
*/

class Solution {
public:
    int res = INT_MIN;
    int diameterOfBinaryTree(TreeNode* root) {
        solve(root);
        return res - 1; // path identified using edges, not nodes
    }

    int solve(TreeNode* root) {
        // Base codnition
        if(root == NULL)
            return 0;
        
        // Hypothesis
        int l = solve(root->left);
        int r = solve(root->right);

        // Induction :

        // If node do not want to be in main ans
        int temp = 1 + max(l, r);

        // If node want to be in main ans
        int ans = 1 + l + r;
        res = max(res, ans);

        // always return temp
        return temp;
    }
};


/*
124. Binary Tree Maximum Path Sum
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. 
A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

- Nodes can be negative as well, so it's possible that we're adding nodes, but decreasing value 
*/

class Solution {
public:
    int res = INT_MIN;
    int maxPathSum(TreeNode* root) {
        solve(root);
        return res;
    }

    int solve(TreeNode* root) {
        // Base codnition
        if(root == NULL)
            return 0;

        // Hypothesis
        int l = solve(root->left);
        int r = solve(root->right);
        
        //Induction:
        // Not a main node
        int temp = max(root->val + max(l, r), root->val);   

        // Becoming the main node
        int ans = max(temp, root->val + l + r);
        res = max(res, ans);

        return temp;
    }
};