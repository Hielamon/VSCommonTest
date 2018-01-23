#include <iostream>
#include <vector>
#include <cassert>

class MyTreeNode
{
public:
	MyTreeNode() 
	{ 
		parent = -1;
		brotherIdx = -1;
	}
	~MyTreeNode(){}

	std::vector<int> children;
	int parent;
	int brotherIdx;
};

std::vector<MyTreeNode> getFullTree(std::vector<int> parents, int rootIdx = -1)
{
	std::vector<MyTreeNode> nodes(parents.size() + 1);

	for (size_t i = 0; i < parents.size(); i++)
	{
		nodes[i + 1].parent = parents[i];
		nodes[i + 1].brotherIdx = nodes[parents[i]].children.size();
		nodes[parents[i]].children.push_back(i + 1);
	}

	//change the tree's root to rootIdx;
	if (rootIdx != -1)
	{
		int trackIdx = rootIdx;
		int parentIdx = nodes[trackIdx].parent;
		nodes[trackIdx].parent = -1;
		
		int trackBrotherIdx = nodes[trackIdx].brotherIdx;
		while (parentIdx != -1)
		{
			int tmpParentIdx = nodes[parentIdx].parent;
			int tmpBrotherIdx = nodes[parentIdx].brotherIdx;

			nodes[parentIdx].parent = trackIdx;
			nodes[parentIdx].brotherIdx = nodes[trackIdx].children.size();
			nodes[trackIdx].children.push_back(parentIdx);

			nodes[parentIdx].children[trackBrotherIdx] = -1;

			trackIdx = parentIdx;
			trackBrotherIdx = tmpBrotherIdx;

			parentIdx = tmpParentIdx;
		}
	}
	return nodes;
}

int getMaxDepth(std::vector<MyTreeNode> &nodes, int rootIdx)
{
	int maxDepth = 1, currentDepth = 1;
	std::vector<bool> visited(nodes.size(), false);

	assert(rootIdx >= 0 && rootIdx < nodes.size() && nodes[rootIdx].parent == -1);

	int nextNodeIdx = rootIdx;
	while (nextNodeIdx != -1)
	{
		//continue find next node idx
		int curNodeIdx = nextNodeIdx;
		visited[curNodeIdx] = true;
		nextNodeIdx = -1;
		for (size_t i = 0; i < nodes[curNodeIdx].children.size(); i++)
		{
			int tmpChildIdx = nodes[curNodeIdx].children[i];
			if (tmpChildIdx != -1)
			{
				if (visited[tmpChildIdx] == true)
				{
					break;
				}
				nextNodeIdx = tmpChildIdx;
				break;
			}
		}

		if (nextNodeIdx == -1)
		{
			int brotherIdx = nodes[curNodeIdx].brotherIdx + 1;
			int parentIdx = nodes[curNodeIdx].parent;
			
			while (parentIdx != -1)
			{
				while (nodes[parentIdx].children.size() > brotherIdx)
				{
					if (nodes[parentIdx].children[brotherIdx] == -1)
					{
						brotherIdx++;
					}
					else
					{
						break;
					}
				}

				if (nodes[parentIdx].children.size() > brotherIdx)
				{
					nextNodeIdx = nodes[parentIdx].children[brotherIdx];
					break;
				}
				else
				{
					brotherIdx = nodes[parentIdx].brotherIdx + 1;
					parentIdx = nodes[parentIdx].parent;
					currentDepth--;
				}
			}
		}
		else
		{
			currentDepth++;
			if (currentDepth > maxDepth)
			{
				maxDepth = currentDepth;
			}
		}
	}
	
	return maxDepth;
}

int main()
{
	int cityNum = 5, stepNum = 2;
	std::vector<int> parents = { 0, 1, 2, 3 };

	while (std::cin >> cityNum && std::cin >> stepNum)
	{
		int i = 0;
		parents.resize(cityNum - 1);
		for (i = 0; i < cityNum - 1; i++)
		{
			std::cin >> parents[i];
		}
		if (i != parents.size())
		{
			std::cout << "Invalid input!!!!" << std::endl;
			break;
		}

		std::vector<MyTreeNode> nodes = getFullTree(parents, 0);
		int maxDepth = getMaxDepth(nodes, 0);
		std::cout << "max tree depth = " << maxDepth << std::endl;
		int residualSteps = stepNum - (maxDepth - 1);
		int result = 0;
		if (residualSteps <= 0)
		{
			result = stepNum + 1;
		}
		else
		{
			int residualCity = residualSteps / 2;
			result = residualCity + stepNum + 1;
			if (result > cityNum)
			{
				result = cityNum;
			}
		}

		std::cout << result << std::endl;
	}

	return 0;
}