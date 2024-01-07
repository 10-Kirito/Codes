class Solution {
    vector<vector<int>> result;
    vector<int> path;
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        //将第一个结点的值放入栈当中：
        path.push_back(0);
        //用来记录是否访问过当前结点：

        dfs(graph, 0);
        
        return result;
    }

    void dfs(vector<vector<int>>& graph, int index) {
        // 发现当前结点为n-1的话，就将当前的路径放入结果当中：
        if(index == graph.size() - 1)
        {
            result.push_back(path);
            return;
        }
        for(auto elem : graph[index]) {
            // 一一将其邻接结点插入路径当中：
            path.push_back(elem);
            dfs(graph, elem);
            // 回溯，将下一个结点插入路径当中：
            path.pop_back();
        }
    }

};
