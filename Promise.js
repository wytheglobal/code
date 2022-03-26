const PENDING = 0;
const FULFILLED = 1;
const REJECTED = 2;

function P(fn) {
    let state = PENDING;
    let value = null;
    let handlers = [];

    function fullfill(result) {
        state = FULFILLED;
        value = result;
        handlers.forEach(handle);
        handlers = null;
    }

    function reject(err) {
        state = REJECTED;
        value = err;
        handlers.forEach(handle);
        handlers = null;
    }

    function resolve(result) {
        try {
            let then = getThen(result);
            if (then) {
                doResolve(then.bind(result), resolve, reject);
                return
            }
            fullfill(result);
        } catch (e) {
            reject(e);
        }
    }

    function handle(handler) {
        if (state === PENDING) {
            handlers.push(handler);
        } else {
            if (state === FULFILLED &&
                typeof handler.onFullfilled === 'function') {
                handler.onFullfilled(value);
            }
            if (state === REJECTED &&
                typeof handler.onRejected === 'function') {
                handler.onRejected(value);
            }
        }
    }

    this.done = function (onFullfilled, onRejected) {
        setTimeout(function () {
            handle({
                onFullfilled: onFullfilled,
                onRejected: onRejected,
            })
        }, 0);
    }

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

function getThen(value) {
    var t = typeof value;
    if (value && (t === 'object' || t === 'function')) {
        var then = value.then;
        if (typeof then === 'function') {
            return then;
        }
    }
    return null;
}

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


// function test() {
//     return new P(function(resolve, reject) {
//         setTimeout(function() {
//             resolve('hello world!');
//         }, 1000)
//     })    
// }

// test().then(data => {
//     console.log(data);
//     return data + data;
// }, err => {
//     console.log(err);
// }).then(data => {
//     console.log(data)
// })

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
