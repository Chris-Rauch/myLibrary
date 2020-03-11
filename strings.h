#ifndef MY_STRINGS
#define MY_STRINGS
#include <string>
#include <iostream>

/* Description:
 *     Returns a string of uppercase letters. Does NOT change input 
 */
std::string upperCase(const std::string &str) {
   std::string newStr;
   size_t strSize = str.size();

   for(size_t i = 0; i < strSize; ++i) {
      newStr.push_back(toupper(str[i]));
   }
   return newStr;
} 

/* Description:
 *     Returns a string of lowercase letters. Does NOT change input
 */
std::string lowerCase(const std::string &str) {
   std::string newStr;
   size_t strSize = str.size();

   for(size_t i = 0; i < strSize; ++i) {
      newStr.push_back(tolower(str[i]));
   }
   return newStr;
} 

/* Descritpion:
 *     Returns levenshtein's edit distance
 */
#define MIN(x,y) ((x) < (y) ? (x) : (y)) 
size_t levenshtein_distance(std::string s1,std::string s2) {
   int t,track;
   int dist[256][256];
   size_t l1 = s1.size();
   size_t l2 = s2.size();

   for(size_t i = 0; i <= l1; ++i) {
      dist[0][i] = i;
   }
   for(size_t j = 0; j <= l2; ++j) {
      dist[j][0] = j;
   }
   for (size_t j = 1; j<= l1; ++j) {
      for(size_t i = 1; i <= l2; ++i) {
         if(s1[i-1] == s2[j-1]) {
            track= 0;
         } else {
            track = 1;
         }
         t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
         dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
      }
   }
   return dist[l2][l1];
}
#endif
