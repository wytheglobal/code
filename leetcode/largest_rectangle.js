/** brutal force */
var largestRectangleArea = function(heights) {
    let maxArea = 0;
    for (let i = 0, l = heights.length; i < l; i++) {
        let h = heights[i];
        let left;
        let right;
        for (left = i ; left >= 0; left--) {
            if (heights[left] < h) {
                break;
            }
        }
        for (right = i; right < l; right++) {
            if (heights[right] < h) {
                break;
            }
        }
        let width = right - left - 1;

        // console.log(left, right, width, h);

        if (width * h > maxArea) {
            maxArea = width * h;
        }
    }
    return maxArea;
};

// console.log(largestRectangleArea([2, 4]));

var largestRectangleArea = function(heights) {
    console.log(heights);
    let stack = [];
    const maxArea = [];
    heights.unshift(0);
    heights.push(0);
    let result = 0;
    for (var i = 0, l = heights.length; i < l; i++) {
        while(stack.length && (heights[i] < heights[stack[stack.length - 1]])) {
            let target = stack.pop();
            let left = stack[stack.length - 1];
            let width = i - left - 1;
            // console.log(`cal: i: ${i} left: left${left} `, stack);
            // if (stack.length === 1) {
            //     width = i - stack[0] - 1;
            //     // stack.pop();
            // }
            // if (!stack.length) {
            //     console.log("empty stack ...");
            // }
            const height = heights[target];
            const area = width * height;
            maxArea[target] = area;
            if (area > result) {
                result = area;
            }
        }
        if (heights[i] === 0) {
            stack = [i];
        } else {
            stack.push(i);
        }
    }
    console.log(maxArea);
    return result;
}


largestRectangleArea([3,6,5,7,4,8,1,0]);

// largestRectangleArea([2,1,5,6,2,3]);

