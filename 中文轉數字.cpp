#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream> 
using namespace std;


#define CHAR_ZERO   CHAR_NUM[0]
#define LEN_NUM     10
#define LEN_SI      3
#define LEN_BI      1

const int MAX_LEN = 20;
const int INTERVAL = 4;


const string CHAR_NUM[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};

const string CHAR_SI[] = {"十", "百", "千"};

const string CHAR_BI[] = {"萬"};

string spellnum(string);


int main() {


    while(1){
	
       string num;
       stringstream ss;
		int i = 0;
       cout << "請輸入中文數字(小於等於10^7): ";
       cin >> num;
    
	  
	  ss<<spellnum(num);
	  
	  ss>>i;
	  
	  if(i<10000000)
	  {
	  	 cout<<i<<endl;
	  }
	  else{
	  	cout<<"error"<<endl;
	  }
	  
	  
	  
	  	  
	 
	  
	    
	    
	   
    }

    return 0;
}


string spellnum(string spell) {
    int val = -1, siNum[INTERVAL] = {0}, biPower = 0, lastBiPower = 0;
    bool isNum, isSi, isBi, valProc, firstNonZero = false;
    string ch;
    string ret;

    if (CHAR_ZERO == spell) {
        return "0";
    }

    for (size_t i = 0; i != spell.size(); i += 2) {
        ch = spell.substr(i, 2);

        
        isNum = false;
        for (int j = 0; j != LEN_NUM; ++j) {
            if (ch == CHAR_NUM[j]) {
                val = j;

                valProc = false;
                isNum = true;
            }
        }

        
        isSi = false;
        if ( !isNum) {
            for (int si = 0; si != LEN_SI; ++si) {
                if (ch == CHAR_SI[si]) {
                    
                    if (-1 == val) {
                        val = 1;
                    }

                    siNum[si + 1] = val;
                    valProc = true;

                    isSi = true;
                }
            }
        }

      
        isBi = false;
        if ( !isSi) {
            for (int bi = 0; bi != LEN_BI; ++bi) {
                if (ch == CHAR_BI[bi]) {
                    lastBiPower = biPower;
                    biPower = (bi + 1) * INTERVAL;

                    lastBiPower -= INTERVAL + biPower;

                    while (lastBiPower > 0) {
                        ret += '0';
                        --lastBiPower;
                    }

                    if ( !valProc) {
                        siNum[0] = val;
                    }

                   
                    for (int si = INTERVAL - 1; -1 != si; --si) {
                        if (0 != siNum[si]) {
                            firstNonZero = true;
                        }

                        if (firstNonZero) {
                            ret += (siNum[si] + '0');
                        }

                        siNum[si] = 0;
                    }

                    isBi = true;
                }
            }
        }
    }

    if (isBi) {
        while (0 != biPower) {
            ret += '0';
            --biPower;
        }
    } else {
        lastBiPower = biPower - INTERVAL;

        while (lastBiPower > 0) {
            ret += '0';
            --lastBiPower;
        }

        if ( !valProc) {
            siNum[0] = val;
        }

        for (int si = INTERVAL - 1; -1 != si; --si) {
            if (0 != siNum[si]) {
                firstNonZero = true;
            }

            if (firstNonZero) {
                ret += (siNum[si] + '0');
            }
        }
    }

    return ret;
}
