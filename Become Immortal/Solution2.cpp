#include <bits/stdc++.h>

#include <bits/stdc++.h>

long long largestPow2(long long i){
    long long p = 1;
    while (p <= i){
        p <<= 1;
    }
    return p >> 1;
}

long long sumRange(long long from, long long to){
    return ((to+from)*(to-from+1)) / 2;
}

long long subdivide(long long x, long long y, long long width, long long height, long long l, long long t){
    printf("Subdivision from (%lld, %lld), w = %lld, h = %lld\n", x, y, width, height);

    if ( width==0 || height == 0) return 0;

    if (height > width){
        std::swap(x, y);
        std::swap(width, height);
    }

    long long ans = 0;

    long long width2 = largestPow2(width);
    long long height2 = largestPow2(height);
    
    // Solve central main block

    long long offset = (x-1)^(y-1);
    long long maxVal = offset + width2-1;
    if (l < maxVal){
        long long row = sumRange(std::max((long long)0, offset-l), maxVal-l);
        if (height2 < width2){
            ans += row * height;
            printf("Range sum from %lld - %lld times %lld\n", std::max((long long)0, offset-l), maxVal-l, height);
        }
        else{
            ans += row * height2;
            printf("Range sum from %lld - %lld times %lld\n", std::max((long long)0, offset-l), maxVal-l, height2);
        }
        ans %= t;
    }

    // Solve below
    if (height2 == width2 && height > height2){
        long long offset = (x-1)^(y+height2-1);
        long long maxVal = offset + width2-1;
        if (l < maxVal){
            ans += sumRange(std::max((long long) 0, offset-l), maxVal-l) * (height-height2);
            printf("Range sum from %lld - %lld times %lld\n", std::max((long long)0, offset-l), maxVal-l, height-height2);
            ans %= t;
        }
    }

    // Solve right
    if (width > width2){
        long long offset = (x+width2-1)^(y-1);
        long long maxVal = offset + height2-1;
        if (l < maxVal){
            ans += sumRange(std::max((long long)0, offset-l), maxVal-l) * (width-width2);
            printf("Range sum from %lld - %lld times %lld\n", std::max((long long)0, offset-l), maxVal-l, width-width2);
            ans %= t;
        }
    }
    
    // Solve final corner
    if (width > width2 && height > height2){
        ans += subdivide(x+width2, y+height2, width-width2, height-height2, l, t);
        ans %= t;
    }
    
    return ans % t;
}


int main(){
    long long w, h, l, t;
    std::cin >> w >> h >> l >> t;
    long long ans = subdivide(1, 1, w, h, l, t);
    printf("%lld\n", ans);
}
