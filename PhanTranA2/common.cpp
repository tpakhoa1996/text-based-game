#include "stdafx.h"

namespace helper {
	string trim(string s) {
		int left = 0, right = s.length();
		while (left < right) {
			if (s[left] == '\n' || s[left] == ' ') {
				left++;
			} else if (s[right - 1] == '\n' || s[right - 1] == ' ') {
				right--;
			} else {
				break;
			}
		}
		return s.substr(left, right - left);
	}
}