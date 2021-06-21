//This code is for a challege from Hacker Rank
//Parses an HRML File

//Sample Input
//First line contains number of tag lines and number of queries
/*  
4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value
*/

//I will use a struct and recursion for my solution

#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

//A Tagmap struct contains a (tagname, tagmap) map of a (attribute name, attribute value) map 
//and a pointer to the next nested Tagmap
typedef struct Tagmap {
    map<string, map<string, string>> tagmap;
    Tagmap* tagmap_ptr = nullptr;
} Tagmap;

//this is a helper function which accepts a tag, parses it, and maps it attributes on the tagmap
string map_tag(string tag_to_map, Tagmap* tagmap) {
    string::iterator it;
    it = tag_to_map.begin();
    string tag_name = "";
    string attribute_name;
    string attribute_value;
    it++; //discard the '<' character
    //get the tagname
    do {
        tag_name += (*it);
        it++;
    } while((*it) != ' ' && (*it) != '>');
    //get the attributes and map them
    while ((*it) != '>') {
        attribute_name = "";
        attribute_value = "";
        it++; //discard space character
        //get attribute name
        do {
            attribute_name += (*it);
            it++;
        } while((*it) != ' ');
        it += 4; //skip spaces and '=' and /" characters to the first character of attribute value
        do {
            attribute_value += (*it);
            it++;
        } while ((*it) != ' ' && (*it) != '>');
        attribute_value.pop_back(); //remove the quotation mark from the end of the attribute value
        tagmap->tagmap[tag_name][attribute_name] = attribute_value;
    }
    //special case to deal with tags that don't have attributes
    if (tag_to_map == ("<" + tag_name + ">")) {
        tagmap->tagmap[tag_name]["NO_ATTRIBUTE"] = "NO_ATTRIBUTE";
    }
    return tag_name;
}


//this is the recursive function which creates tagmaps and nested tagmaps
void create_tagmap (list<string>& tags, Tagmap* pretagmap) {
    string tag;
    string tag_name = "";
    
    tag = tags.front();
    tags.pop_front();
    //map a tag
    tag_name = map_tag(tag, pretagmap);
    tag = tags.front();
    //while this tags ending tag is not found
    while (tag != "</" + tag_name + ">") {
        //if nested tagmap already exists, go to it
        if (pretagmap->tagmap_ptr) {
            create_tagmap(tags, pretagmap->tagmap_ptr);
        }
        //else create a new tagmap and go to it
        else {
            pretagmap->tagmap_ptr = new Tagmap;
            create_tagmap(tags, pretagmap->tagmap_ptr);
        }
        tag = tags.front(); //get the next tag so the loop can check for the current tags end tag
    }
    //current tags end tag was found, so pop it and return
    tags.pop_front();
}

//this function recursively performs a query against nested tag maps
//each query is broken until just the attribute name and value exists
//if a tagname or tagmap doesn't exist, the function returns "Not Found!"
string perform_query(string query, Tagmap* tagmap) {
    string tag_name = "";
    size_t pos = query.find(".");
    string answer = "";
    string attribute_name;
    //not full query, so go deeper
    if (pos != -1) {
        tag_name = query.substr(0, pos);
        //check that tag exists in the tagmap
        try {
            tagmap->tagmap.at(tag_name);
            //exists,
            //only travel further if a lower tagmap exists
            if (tagmap->tagmap_ptr) {
                answer = perform_query(query.substr(pos + 1), tagmap->tagmap_ptr);
            }
            else {
                answer = "Not Found!";
            }
        }
        catch (const out_of_range& e) {
            answer = "Not Found!";
        }
    }
    //else check if attribute exists
    else {
        pos = query.find("~");
        tag_name = query.substr(0, pos);
        attribute_name = query.substr(pos + 1);
        try {
            answer = tagmap->tagmap.at(tag_name).at(attribute_name);
        }
        catch (const out_of_range& e) {
            answer = "Not Found!";
        }
    }
    return answer;
}

//function frees up memory
void destroy_tagmaps(Tagmap* tagmap) {
    if (tagmap->tagmap_ptr) {
        destroy_tagmaps(tagmap->tagmap_ptr);
    }
    delete tagmap;
}

int main() {
    int number_tags;
    int number_queries;
    list<string> queries;
    list<string> tags;
    string input;
    Tagmap* roottagmap = new Tagmap;
    
    cin >> number_tags >> number_queries;
    cin.ignore();

    //store the tags and queries in lists
    for (int i = 0; i < number_tags; i++) {
        getline(cin, input);
        tags.push_back(input);
    }
    for (int i = 0; i < number_queries; i++) {
        getline(cin, input);
        queries.push_back(input);
    }

    //start the recursive tagmap creations
    while (!tags.empty()) {
        create_tagmap(tags, roottagmap);
    }

    //perform the queries
    for (int i = 0; i < number_queries; i++) {
        cout << perform_query(queries.front(), roottagmap) << endl;
        queries.pop_front();
    }

    destroy_tagmaps(roottagmap);

    return 0;
}