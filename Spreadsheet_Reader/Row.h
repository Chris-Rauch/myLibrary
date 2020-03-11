/* @ Row.h
 * DESCRIPTION: 
 * The Row class will help parse deliminated files. Default is csv 
 * (comma seperated value) with a comma used as the delimiter. Otherwise, 
 * specify the delimiter you want to use when constructing the object. 
 * 
 * The overloaded insertion and extraction operators make it easy to read and 
 * write lines to a file.
 *     Ex. Row row(',');
 *         fileStreamObject >> row;
 *         fileStreamObject << row;
 * 
 * Easy access to row elements
 *     Ex. string rowElem = row[0]; 
 * 
 * NOTE* - This class automatically removes any commas that are inside quotes. 
 *     Ex. {row,of,data,"1,125.00"} --> {row,of,data,1125.00}
 */ 

#ifndef ROW
#define ROW

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Row {
    public:
        // Constructers
        Row() : delimiter(',') {}
        Row(char d) : delimiter(d) {} 
    public:
        // Modifiers
        void changeCell(int i, string data) {row_[i] = data;}
        void trim();
        void removeTrailingDelimiter();
        void replaceAll(const string& before, const string& after);
        void nextRow(istream& inFile);

        //Accessors
        string const& operator[](size_t index) const {return row_[index];}
        size_t size() const {return row_.size();}
        char const getDelim() const {return delimiter;}

        //Sort
        static const bool sortFunction(const Row& rhs,const Row& lhs){return lhs.row_[0] < rhs.row_[0];}
          
    private:   
        void removeCommasInQuotes(string& line);

    private:
        vector<string> row_;
        char delimiter;
};

/* Description: Reads a single line of data. Removes commas that are inside
 *              quotes.
 * Input: [inFile] - The csv filestream object
 * Output: Moves the filestream forward one line. *This is populated with data
 */
void Row::nextRow(istream& inFile) {
    string cell, line;

    getline(inFile,line);
    if(this->delimiter == ',')
        removeCommasInQuotes(line);
    stringstream ss(line);
            
    row_.clear();
    while(getline(ss,cell,delimiter)) 
        row_.push_back(cell);
}

/* Description: Removes all trailing delimiters of a row. 
 * Input: None
 * Output: This->size() may be altered
 */
void Row::removeTrailingDelimiter() {
    bool isEmpty = true;

    for(size_t i = (this->size()-1); (i >= 0) && (isEmpty == true); --i) {
        if(row_[i] != "") {
            isEmpty = false;
        }
        if(isEmpty) {
            row_.pop_back();
        }
    }
}

/* Description: Replaces all instances of 'before' with 'after.' All cells in a
 *              row are affected.
 * Input: [before] - The search value
 *        [after]  - The replacement value
 * Output: None
 */
void Row::replaceAll(const string& before, const string& after) {
    for(size_t i = 0,found; i < this->size(); ++i) 
        while(string::npos != (found=row_[i].find(before))) 
            row_[i].replace(found,before.size(),after);
}

/* Description: This function removes commas inside of quotes. The quotes are
 *              also removed. This function is called automatically when 
 *              receiving input.
 * Input: [line] - A row of data represented as a single string
 * Output: None
 */
void Row::removeCommasInQuotes(string& line) {
    bool flag = false;
    
    for(int i = 0; i < line.size(); ++i) {
        if(line[i] == '\"') {
            flag = !flag;
            line.erase(i,1);
        }
        if(flag && (line[i] == ',')) {
            line.erase(i,1);
        }
    } 
}

/* Description: Removes leading and trailing white space from all cells
*/
void Row::trim() {
    for(int i = 0; i < row_.size();++i) {
        size_t first = row_[i].find_first_not_of(' ');
        if (string::npos != first) {
            size_t last = row_[i].find_last_not_of(' ');
            row_[i] = row_[i].substr(first, (last - first + 1));
        }
    }
}

/* Description: Overloaded extraction operator
 */
inline istream& operator>>(istream& fileStream,Row& data) {
    data.nextRow(fileStream);
    return fileStream;
}

/* Description: Overloaded insertion operator
 */
inline ostream& operator<<(ostream& cout,Row data) {
    const size_t dataSize = data.size();
    for (size_t i = 0; i < dataSize; ++i) {
        cout << data[i];
        if(i < (dataSize-1))
            cout << data.getDelim();
    }
    return cout;
}
#endif
