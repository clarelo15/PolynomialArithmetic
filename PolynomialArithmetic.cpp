//
//  main.cpp
//  Lo_YinYu_p6
//
//  Created by yin yu lo on 12/6/20.
//  Copyright © 2020 yin yu lo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

void outputCanonical(std::map<int, int>& poly, ofstream &file);

int main() {
    map<int, int> poly1, poly2, sum, sub, product;
    string line1, line2;
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    if(input.is_open()){
        while(!input.eof()){
            getline(input, line1);
            getline(input, line2);
            stringstream s1(line1);
            stringstream s2(line2);
            int e, c;
            
            output << "initial input:" << endl;
            poly1 = {};
            while(s1 >> c >> e){
                output << c << " " << e << " ";
                cout << "c " << c << " e " << e << endl;
                poly1[e] += c;
                if(poly1[e] == 0)
                    poly1.erase(e);
            }
            output << endl;
            
            poly2 = {};
            while(s2 >> c >> e){
                output << c << " " << e << " ";
                cout << "c " << c << " e " << e << endl;
                poly2[e] += c;
                if(poly2[e] == 0)
                    poly2.erase(e);
            }
            output << endl << endl;
            map<int, int>::reverse_iterator p;
            
            cout<<endl<<"this was the first polynomial"<<endl;
            for(p=poly1.rbegin();p!=poly1.rend();p++)
            {cout<<(*p).second<<" "<<(*p).first<<endl;
            }
            output << "this is the first polynomial : ";
            outputCanonical(poly1, output);
            
            cout<<endl<<"this was the second polynomial"<<endl;
            for(p=poly2.rbegin();p!=poly2.rend();p++)
            {cout<<(*p).second<<" "<<(*p).first<<endl;
            }
            
            output << "this is the second polynomial : ";
            outputCanonical(poly2, output);
            
            sum=poly1;
            // now "add poly2 to sum
            for(p=poly2.rbegin();p!=poly2.rend();p++) {
                sum[p->first]+=p->second;
                if(sum[p->first]==0)
                    sum.erase(p->first);
            }
            // print the sum of poly1 + poly2
            cout<<endl<<"this is sum polynomial"<<endl;
            for(p=sum.rbegin();p!=sum.rend();p++) {
                cout<<(*p).second<<" "<<(*p).first<<endl;
            }
            output << "this is the sum polynomial : ";
            outputCanonical(sum, output);
            
            sub=poly1;
            // now subtract poly2 to sub
            for(p=poly2.rbegin();p!=poly2.rend();p++) {
                sub[p->first]-=p->second;
                if(sub[p->first]==0)
                    sub.erase(p->first);
            }
            // print the sub of poly1 - poly2
            cout<<endl<<"this is subtract polynomial"<<endl;
            for(p=sub.rbegin();p!=sub.rend();p++) {
                cout<<(*p).second<<" "<<(*p).first<<endl;
            }
            output << "this is the subtract polynomial : ";
            outputCanonical(sub, output);
            
            map<int, int>::reverse_iterator k;
            product = {};
            //product=poly1;
            // now multiply poly2 to product
            for(p=poly2.rbegin();p!=poly2.rend();p++) {
                for(k=poly1.rbegin();k!=poly1.rend();k++){
                    product[p->first + k->first]+=p->second * k->second;
                    if(product[p->first + k->first]==0)
                        product.erase(p->first + k->first);
                }
            }
            // print the product of poly1 * poly2
            cout<<endl<<"this is multiplication polynomial"<<endl;
            for(p=product.rbegin();p!=product.rend();p++) {
                cout<<(*p).second<<" "<<(*p).first<<endl;
            }
            cout << endl;
            output << "this is the multiplication polynomial : ";
            outputCanonical(product, output);
            output << endl;
        }
    }
    
    input.close();
    output.close();
    return 0;
}

void outputCanonical(std::map<int, int>& poly, ofstream &file){
    map<int, int>::reverse_iterator p;
    if(poly.empty()){
        file << "0";
    }
    for (p = poly.rbegin();p != poly.rend();p++){
        if((*p).second == 1){
            if((*p).second > 0 && p != poly.rbegin())
                file << "+";
            if((*p).first == 1)
                file << "x";
            else if((*p).first == 0){
                file << (*p).second;
            }
            else{
                file << "x^" << (*p).first;
            }
        }
        else if((*p).first == 1){
            if((*p).second > 0 && p != poly.rbegin())
                file << "+";
            if((*p).second == 1)
                file << "x";
            else if((*p).second == -1)
                file << "-x";
            else{
                file << (*p).second << "x";
            }
        }
        
        else if((*p).first == 0){
            if((*p).second > 0 && p != poly.rbegin())
                file << "+";
            file << (*p).second;
        }
        
        else{
            if((*p).second > 0 && p != poly.rbegin())
                file << "+";
            if((*p).first == 1 && (*p).second == 1)
                file << "x";
            else if((*p).second == 1){
                file << "x^" << (*p).first;
            }
            else if((*p).second == -1){
                file << "-x^" << (*p).first;
            }
            else{
                file << (*p).second << "x^" << (*p).first;
            }
            
        }
    }
    file << endl;
}
