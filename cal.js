function isDigit(c) {
    return /^[0-9]$/.test(c);
}

// 1+3*4/2-1*(3+1)
function calculator(str) {
    let stack = [];

    let i = 0;
    let l = str.length;

    const NUMBER = 10000;
    const UNKNOW = 20000;

    const IMMEDIATE_OPERATOR = 10200;
    const LOW_PRIORITY_OPERATOR = 10201;

    const L_PARENTHESIS = 10100;
    const R_PARENTHESIS = 10101;
    
    let tokenVal;
    let tokenType;

    function getToken() {
        console.log(i, l);
        if (i >= l) { 
            tokenType = null; 
            return tokenType;
        }
        let c = str[i];
        i++;
        if (c === ' ') {
            c = str[i];
            i++;
        }
        if (isDigit(c)) {
            let num = c - 0;
            while (isDigit(str[i])) {
                num = num * 10 + (str[i] - 0);
                i++;
                console.log(i);
            }
            // return num;
            tokenType = NUMBER;
            tokenVal = num;
        } else if(c === '*' || c === '/'){
            tokenType = IMMEDIATE_OPERATOR;
            tokenVal = c;
        } else if (c === '+' || c === '-') {
            tokenType = LOW_PRIORITY_OPERATOR;
            tokenVal = c;
        } else if (c === '(') {
            tokenType = L_PARENTHESIS;
            tokenVal = c;
        } else if (c === ')') {
            tokenType = R_PARENTHESIS;
            tokenVal = c;
        } else {
            tokenType = UNKNOW;
            tokenVal = c;
        }
        return tokenType;
    }


    function normalCal(pool) {
        let result = 0;
        for (let i = 0, l = pool.length; i < l; i++) {
            let token = pool[i];
            if (token === '+') {
                result += pool[++i];
            } else if (token === '-') {
                result -= pool[++i];
            } else {
                result += pool[i];
            }
        }
        return result;
    }

    function matchLParenthesisCall() {
        let pool = []
        let token = stack.pop();
        let num = 0;
        while (token !== undefined && token !== '(') {
            pool.unshift(token)
            token = stack.pop();
        }
        const val = normalCal(pool);
        // handleToken();
        // console.log(stack, result);
        tokenType = NUMBER;
        tokenVal = val;
        handleToken();
    }


    function handleToken() {
        switch (tokenType) {
            case NUMBER:
                let prevToken = stack[stack.length - 1];
                if (prevToken === '*') {
                    stack.pop()
                    let num = stack.pop();
                    stack.push(num * tokenVal);
                } else if (prevToken === '/') {
                    stack.pop()
                    let num = stack.pop();
                    stack.push(num / tokenVal);
                } else {
                    stack.push(tokenVal);
                }
                break;
            case L_PARENTHESIS:
                stack.push(tokenVal);
                break;
            case R_PARENTHESIS:
                // stack.push(tokenVal);
                matchLParenthesisCall();
                break;
            case IMMEDIATE_OPERATOR:
            case LOW_PRIORITY_OPERATOR:
                stack.push(tokenVal);
                break;
            default:
                console.log("unknow token type:", tokenType, " val:", "'"+tokenVal+"'");
        }   
    }

    while (getToken() !== null) {
        console.log(tokenType);
        handleToken();
    }
    // for (let i = 0, l = str.length; i < l; i++) {
    //     let token = str[i];


    //     if (isDigit(token)) {
    //         let num = token - 0;
    //         while (isDigit(str[i+1])) {
    //             num = num * 10 + (str[i+1] - 0);
    //             i++;
    //         }
    //         stack.push(num);
    //     } else if ()
    // }
    console.log(stack)
    console.log(normalCal(stack));
}

// calculator("1 + 123 * (2 - 6 / 3 + 10)")
calculator('-1+3*4/2-1*(3*(1+2))');