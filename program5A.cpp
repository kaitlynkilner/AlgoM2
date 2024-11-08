#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
/* Solution to program 5A
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<std::vector<int>,std::vector<int>,std::vector<int>,std::vector<int>,int,int,int,std::vector<int>> findArray(std::vector<int> heights, std::vector<int> widths, std::vector<int> &arr, std::vector<int> &nums, int n, int W, int &ind,std::vector<int> &width){
    //return max(n-1 or n), in function check if new platform needs to be created
    if(arr[n] != -1){
        return std::make_tuple(heights,widths,arr,nums,n,W-widths[n],ind,width);
    }
    if(n==0){
        arr[0] = heights[0];
        nums.push_back(1);
        width[n] =widths[n];
        return std::make_tuple(heights,widths,arr,nums,n,W,ind,width);
    }
    if(std::max(std::get<2>(findArray(heights,widths,arr,nums,n-1,W,ind,width))[n-1],heights[n])<=arr[ind-1]+heights[n] && width[n-1]+widths[n] <= W){
        if(ind != 1){
            arr[n] = std::max(arr[n-1],arr[ind-1]+heights[n]);}
        else{
            arr[n] = std::max(arr[n-1], heights[n]);
        }
        nums[nums.size()-1]+=1;
        width[n] = width[n-1]+widths[n];
        return std::make_tuple(heights,widths,arr,nums,n,W, ind,widths);
    }
    else{
        arr[n] = arr[n-1]+heights[n];
        nums.push_back(1);
        int k = n;
        int width_k = widths[n];
        width[n] = widths[n];
        ind = n;
        while(width_k+widths[n] <= W){
            //checking if adding previous painting to new platform is better
            if(width_k+widths[n] <= W && std::max(heights[k],heights[k-1])+arr[k-2] < heights[k]+arr[k-1]){
                arr[n] = std::max(heights[n], heights[k-1])+arr[k-2];
                nums[nums.size()-1]+=1;
                nums[nums.size()-2]-=1;
                width_k+=widths[k];
                k--;
            }
            else{
                break;
            }
        }
        return std::make_tuple(heights,widths,arr,nums,n,W, n,width);
    }
}

std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    //initialize with negative 1
    std::vector<int> arr(n,-1);
    std::vector<int> nums;
    std::vector<int> width(n,0);
    int ind = 1;
    //basecases
    auto result = findArray(heights,widths,arr,nums,n-1,W,ind,width);
    nums.erase(std::remove(nums.begin(),nums.end(),0),nums.end());
    return std::make_tuple(nums.size(),arr[n-1],nums);
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
    auto result = program5A(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}
