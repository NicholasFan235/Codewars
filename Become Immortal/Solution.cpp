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

long long solvePow2Square(long long x, long long y, long long height, long long l, long long t){
    long long offset = (x-1)^(y-1);
    //printf("Square at (%ld, %ld), size = %ld, offset = %ld\n", x, y, height, offset);

    long long maxVal = offset + height-1;
    if (l > maxVal) return 0;
    //printf("summing range %ld - %ld = ", std::max((long)0, offset-l), maxVal-l);
    long long ans = sumRange(std::max((long long)0, offset-l), maxVal-l) * height;
    ans %= t;
    //printf("%lld\n", ans);
    return ans;
}

long long subdivide(long long x, long long y, long long width, long long height, long long l, long long t){
    //printf("Subdivision from (%lld, %lld), w = %lld, h = %lld\n", x, y, width, height);

    if (height > width){
        std::swap(x, y);
        std::swap(width, height);
    }

    long long ans = 0;
    long long squareSide = largestPow2(height);
    
    // Solve central main block
    long long i = x;
    while (i-x+squareSide <= width){
        ans += solvePow2Square(i, y, squareSide, l, t);
        i += squareSide;
    }

    /*
    // Solve right
    if (i-x < width){
        long long offset = (i-1)^(y-1);

        long long maxVal = offset + squareSide-1;
        if (l < maxVal){
            ans += sumRange(std::max((long long)0, offset-l), maxVal-l) * (width-i+1);
            ans %= t;
        }
    }

    // Solve below
    if (height > squareSide){
        long long offset = (x-1)^(squareSide+y-1);

        long long maxVal = offset + squareSide-1;
        if (l < maxVal){
            ans += sumRange(std::max((long long)0, offset-l), maxVal-l) * (height-squareSide);
            ans %= t;
        }
    }

    // Solve final corner
    if (i-x < width && height > squareSide){
        ans += subdivide(x+squareSide, y+squareSide, width-squareSide, height-squareSide, l, t);
        ans %= t;
    }*/

    
    // Recursive call on leftover right
    //printf("i = %ld, x = %ld, y = %ld, squareSide = %ld, w = %ld, h = %ld\n", i, x, y, squareSide, width, height);
    if (i-x < width){
        //printf("Right\n");
        ans += subdivide(i, y, width-i+1, squareSide, l, t);
    }

    // Recursive call on leftover below
    if (height > squareSide){
        //printf("Below\n");
        ans += subdivide(x, y+squareSide, width, height-squareSide, l, t);
    }
    
    return ans % t;
}


int main(){
    long long w, h, l, t;
    std::cin >> w >> h >> l >> t;
    long long ans = subdivide(1, 1, w, h, l, t);
    printf("%lld\n", ans);
}