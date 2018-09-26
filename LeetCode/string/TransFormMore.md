```
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morse = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",      
                                "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",   
                                "...-",".--","-..-","-.--","--.."};
        
        unordered_set<string> unSet; 

        if(words.size() > 100) return 0;
        for(auto iter = words.begin(); iter!=words.end(); iter++)
        {
            string word = *iter;
            string result = "";
            for(auto c:word)
            {
                int i = c-'a';
                result+=morse[i];
            }
            unSet.insert(result);
        }
        return unSet.size();
    }
};
```
