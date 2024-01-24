#include <iostream>
#include <vector>

#include "TestTools.h"

void __KMP_base(const std::vector<auto>& source,const std::vector<auto>& target,const std::vector<auto>& decline,std::vector<auto>& result,size_t matchEnd)
{
	result.resize(source.size()+1,0);
	size_t matchLength = 0;
	while(matchEnd != source.size())
	{
		if(source[matchEnd] == target[matchLength])
		{
			matchEnd ++;
			matchLength ++;
			result[matchEnd] = matchLength;
			if(matchLength == target.size())
			{
				matchLength = decline[matchLength];
			}
		}
		else
		{
			//mismatch at matchEnd
			if(matchLength == 0)
			{
				//give up here, next
				matchEnd ++;
			}
			matchLength = decline[matchLength];
		}
	}
}

auto __getDecline(const std::vector<auto>& target)
{
	std::vector<size_t> decline;
	
	__KMP_base(target,target,decline,decline,1);
	
	return decline;
}

auto getMatch(const std::vector<auto>& source,const std::vector<auto>& target)
{
	auto decline = __getDecline(target);
	
	std::vector<size_t> result;
	
	__KMP_base(source,target,decline,result,0);
	
	return result;
}

auto getMatchIndex(const std::vector<auto>& source,const std::vector<auto>& target)
{
	auto match = getMatch(source,target);
	
	std::vector<size_t> matchIndex;
	
	for(size_t i = 0;i < match.size();i ++)
	{
		if(match[i] == target.size())
		{
			matchIndex.push_back(i);
		}
	}
	
	return matchIndex;
}

int main()
{
	std::vector source {1,9,1,9,8,1,0};
	std::vector target {1};
	
	test_view(source);
	test_view(target);
	test_view(__getDecline(target));
	test_view(getMatch(source,target));
	test_view(getMatchIndex(source,target));
	
	return 0;
}
