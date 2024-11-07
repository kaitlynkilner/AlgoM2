#include <iostream>
#include <vector>
#include <tuple>
/* Solution to program 5B
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program5B(int n, int W, std::vector<int> heights, std::vector<int> widths){
    int *arr = new int[n];
    //basecases
    arr[0] = 0;
    arr[1] = heights[0];
    int width = widths[0];
    //index for vectors
    int j = 1;
    //platform count
    int plat = 1;
    std::vector<int> nums;
    nums.push_back(1);
    //index of current platform
    int ind = 1;
    for(int i = 2; i < n+1; i++){
        //if adding to preexisting platform
        if(width+widths[j] <= W && std::max(arr[i-1],heights[i]) <= arr[i-1]+heights[i]){
            arr[i] = std::max(arr[i-1],arr[ind-1]+heights[j]);
            nums[plat-1] +=1;
            width+=widths[j];
            j++;
            
        }
        else{
            arr[i] = arr[i-1]+heights[j];
            width=widths[j];
            nums.push_back(1);
            ind=i;
            int k = i;
            while(width<=W){
                //checking if adding previous painting to new platform is better
                if(width+widths[j]<=W && std::max(heights[k-1],heights[k-2])+arr[k-2] < heights[k-1]+arr[k-1]){
                    arr[i] = std::max(heights[j], heights[k-2])+arr[k-2];
                    nums[plat]+=1;
                    nums[plat-1]-=1;
                    width+=widths[k-1];
                    k--;
                }
                else{
                    break;
                }
            }
            j++;
            plat++;
        }
    }
    int val = arr[n];
    delete[] arr;
    return std::make_tuple(plat, val, nums);
}
int main(){
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);
    for(int i = 0; i < n; i++){
        std::cin >> heights[i];
    }
    for(int i = 0; i < n; i++){
        std::cin >> widths[i];
    }
    auto result = program5B(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}

