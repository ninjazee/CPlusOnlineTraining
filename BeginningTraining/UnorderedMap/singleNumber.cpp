#include <vector>
#include <unordered_map>

using namespace std;

int singleNumber(vector<int>& nums) {
	unordered_map<int, int> count; 
	count.reserve(nums.size());

	for (int i = 0; i < (int)nums.size(); i++)
	{
		auto pnt = count.find(nums[i]);
		if (pnt == count.end())
		{
			// Not find
			count[nums[i]] = i; 
		}
		else
		{
			count.erase(pnt);
		}
	}
	auto pnt = count.begin(); 
	return pnt->second;
}