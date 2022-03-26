const PENDING = 0;
const FULLFILLED = 1;
const REJECTED = 2;

function P(fn) {
    let state = PENDING;
    let value = null;
    /**
     * element 
     *  {
     *    onFullfilled: fn,
     *    onRejected: fn,
     *  }
     */
    let handlers = [];

    function handle(handler) {
        if (state === PENDING) {
            handlers.push(handler);
        } else if (state === FULLFILLED && 
            typeof handler.onFullfilled === 'function' ) {
            handler.onFullfilled(value);
        } else if (state === REJECTED && 
            typeof handler.onRejected === 'function') {
            handler.onRejected(value);
        }
    }

    function fullfill(result) {
        state = FULLFILLED;
        value = result;
        handlers.forEach(handle);
        handlers = null;
    }
    function reject(result) {
        state = REJECTED;
        value = result;
        handlers.forEach(handle);
        handlers = null;
    }
    // result maybe another promise
    function resolve(result) {
        try {
            const then = getThen(result);
            if (then) {
                doResolve(then.bind(result), resolve, reject);
                // will be fullfilled in deeper doResolve invoking
                // so we need return here
                return;
            }
            fullfill(result);
        } catch (e) {
            reject(e)
        }
    }

    this.done = function(onFullfilled, onRejected) {
        setTimeout(function() {
            handle({
                onFullfilled: onFullfilled,
                onRejected: onRejected,
            })
        }, 0);
    };

    this.then = function (onFulfilled, onRejected) {
        var self = this;

        return new P(function (resolve, reject) {
            return self.done(function (result) {
                if (typeof onFulfilled === 'function') {
                    try {
                        return resolve(onFulfilled(result));
                    } catch (ex) {
                        return reject(ex);
                    }
                } else {
                    return resolve(result);
                }
            }, function (error) {
                if (typeof onRejected === 'function') {
                    try {
                        return resolve(onRejected(error));
                    } catch (ex) {
                        return reject(ex);
                    }
                } else {
                    return reject(error);
                }
            });
        });
    }

    doResolve(fn, resolve, reject);
}


// // make sure only be called once
// function doResolve(fn, onFullfilled, onRejected) {
//     let done = false;
//     try {
//         // pass function as Promise resolver params
//         // to get Promise value when invoking fullfill/reject
//         fn(function(value) {
//             if (done === true) return;
//             done = true;
//             onFullfilled(value);
//         }, function(err) {
//             if (done === true) return;
//             done = true;
//             onRejected(err);
//         });
//     } catch (e) {
//         onRejected(e);
//     }
// }
function doResolve(fn, onFullfilled, onRejected) {
    let done = false;
    try {
        fn(function (value) {
            if (done) return;
            done = true;
            onFullfilled(value);
        }, function (err) {
            if (done) return;
            done = true;
            onRejected(err)
        })
    } catch (e) {
        if (done) return
        done = true
        onRejected(e)
    }
}

function getThen(value) {
    const t = typeof value;
    if (value && (t === 'object' || t === 'function')) {
        const then = value.then;
        if (then && typeof then === 'function') {
            return then
        }
    }
    return null;
}


function test() {
    return new P(function(resolve, reject) {
        setTimeout(function() {
            resolve("hello world!");
        }, 1000);
    });
}

test().then(data => {
    console.log(data);
}).then(() => {
    return new P(function(resolve, reject) {
        resolve("tomwang")
    });
}).then((data) => {
    console.log(data);
})