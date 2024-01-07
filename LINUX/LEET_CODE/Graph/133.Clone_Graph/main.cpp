/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    // 注意！！！对于图的克隆的话，我们在克隆的时候需要去检查我们是否已经克隆过这个结点，如果我们克隆过了，
    // 我们应该将之前复制品进行赋值，而不是重新创建一个新的样本。
    // 如果你创建一个新的样本的话，就会导致拷贝的图多了几个一样的结点！
    Node* cloneGraph(Node* node) {
        // 如果图是空的话，我们就直接返回空就好了：
        if(!node) return nullptr;
        // 如果图只有一个结点，只需复制该结点接着返回即可：
        if(node->neighbors.empty()) {
            Node* copy = new Node(node->val);
            return copy;
        }
        unordered_map<Node*, Node*> mp;
        // 深度优先遍历图，mp用来记录当前结点是否已经复制
        return dfs(node, mp);
    }

    Node* dfs(Node* node, unordered_map<Node*, Node*> &mp) {
        vector<Node*> neighbors;
        Node* clone = new Node(node->val);
        mp[node] = clone;
        for(auto elem : node->neighbors) {
            // 如果我们在之前的哈希表当中寻找到了我们复制过的结点的话，就无需再次进行复制
            // 只需要将之前复制过的拿过来就行了！
            if(mp.find(elem) != mp.end()) {
                neighbors.push_back(mp[elem]);
            }else{
                // 如果没有找到的话，说明这个结点之前我们没有遍历到过，我们需要继续对其进行深度遍历：
                neighbors.push_back(dfs(elem, mp));
            }
        }

        clone->neighbors = neighbors;
        return clone;
    }
};
