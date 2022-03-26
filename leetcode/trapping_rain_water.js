var trap = function(height) {
    let ans = 0;
    const stack = [];
    const n = height.length;
    for (let i = 0; i < n; ++i) {
        // if right side higher than stack top element, then should calculate water
        while (stack.length && height[i] > height[stack[stack.length - 1]]) {
            const top = stack.pop();
            console.log("pop top: ", top);
            if (!stack.length) {
                break;
            }
            const left = stack[stack.length - 1];
            const currWidth = i - left - 1;
            const currHeight = Math.min(height[left], height[i]) - height[top];
            console.log("calculate pool size: ", left, i, "height: ", currHeight);
            ans += currWidth * currHeight;
        }
        stack.push(i);
        console.log(stack);
    }
    return ans;
};


const height = [0,1,0,2,1,0,2,3,2,1,2,1];
// console.log(trap(height));


function calPoolSize(height) {
    console.log(height);
    const stack = [];
    let size = 0;
    for (let i = 0; i < height.length; i++) {
        // stack's elements height should decreased 
        // if height[i]'s height is higher,
        // height[i] is right side 
        // pop up stack's 
        // top element as bottom, element below stack top is left side
        // width (i - left - 1 )
        // height ( min(height[left], height[right]) - min(height[top]) ) 
        while (stack.length && ( height[i] > height[stack[stack.length - 1]] )) {
            let top = stack.pop();
            if (!stack.length) {
                continue;
            }
            let left = stack[stack.length - 1];
            const width = i - left - 1;
            const leftHeight = height[left];
            const rightHeight = height[i];
            const areaHeight = (leftHeight < rightHeight ? leftHeight : rightHeight) - height[top];
            size += width * areaHeight;
        }
        stack.push(i);
    }
    return size;
}

console.log(calPoolSize(height));