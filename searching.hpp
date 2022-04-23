#include <iostream>
using namespace std;

/* The simplest algorithm in searching algorithm.
It returns location of x in given array arr[] is present, otherwise -1 */
int linear_search(int arr[], int n, int x){
	int i;
	for (i = 0; i < n; i++)
		if (arr[i] == x)
			return i;
	return -1;
}

/* A helper function recursive binary search */
int bsearch(int arr[], int b, int e, int x){
    if (e >= b) {
        int mid = b + (e - b) / 2;
        // If the element is present at the middle itself
        if (arr[mid] == x)
            return mid;
        // If element is smaller than mid, then it can only be present in left subarray
        if (arr[mid] > x)
            return bsearch(arr, b, mid - 1, x);
        // Else the element can only be present in right subarray
        return bsearch(arr, mid + 1, e, x);
    }
    // When element is not present in array
    return -1;
}

/* The binary search function. It returns
location of x in given array arr[] is present, otherwise -1
*/
int binary_search(int arr[], int n, int x){
    return bsearch(arr, 0, n-1, x);
}

void computeLPSArray(char* pat, int M, int* lps);
  
// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt){
    int M = sizeof(pat) / sizeof(pat[0]);
    int N = sizeof(txt) / sizeof(txt[0]);
  
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
  
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
  
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while(i < N){
        if (pat[j] == txt[i]){
            j++;
            i++;
        }
  
        if (j == M){
            cout << "Found pattern at index" << i - j;
            j = lps[j - 1];
        }
  
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]){
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
  
// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps){
    // length of the previous longest prefix suffix
    int len = 0;
  
    lps[0] = 0; // lps[0] is always 0
  
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M){
        if (pat[i] == pat[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                len = lps[len - 1];
  
                // Also, note that we do not increment
                // i here
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

/* main example
int main(void){
	int arr[] = { 2, 3, 4, 10, 40 };
	int x = 10;
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function call
	int result = binary_search(arr, n, x);
	(result == -1)
		? cout << "Element is not present in array"
		: cout << "Element is present at index " << result;
	return 0;
}
*/
