#include <bits/stdc++.h>


int main(){
    int w, h, l, t;
    std::cin >> w >> h >> l >> t;

    long long ans = 0;

    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            int time = i^j;
            //printf("%d, %d, i^j = %d\n", i, j, i^j);
            if (time > l){
                ans += time-l;
            }
        }
    }

    std::cout << ans % t << std::endl;
}