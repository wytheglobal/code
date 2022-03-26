const PENDING = 0;
const FULLFILLED = 1;
const REJECTED = 2;

function P (fn) {
    let state = PENDING;
    let value = null;
    let handlers = [];

    function handle(opt) {
        if (state !== PENDING) {
            if (state === FULLFILLED) {
                return opt.onFullfilled && opt.onFullfilled(value);
            }
            if (state === REJECTED) {
                return opt.onRejected && opt.onRejected(value);
            }
        } else {
            handlers.push(opt);
        }
    }

    function resolve(value) {
        try {
            const then = getThen(value);
            if (then) {
                return doResolve(then.bind(value), resolve, reject);
            }
            fullfill(value);
        } catch (e) {
            reject(e);
        }
    }

    function fullfill(val) {
        state = FULLFILLED;
        value = val;
        handlers.forEach(handle);
        handlers = null;
    }

    function reject(err) {
        state = REJECTED;
        value = err;
        handlers.forEach(handle);
        handlers = null;
    }

    this.done = function(onFullfilled, onRejected) {
        setTimeout(function() {
            handle({
                onFullfilled,
                onRejected,
            })
        }, 0);
    }


    this.then = function(onFulfilled, onRejected) {
        let self = this;
        return new P(function(resolve, reject) {
            self.done(function(value) {
                if (typeof onFulfilled === 'function') {
                    try {
                        resolve(onFulfilled(value));
                    } catch (e) {
                        reject(e);
                    }
                } else {
                    resolve(onFulfilled);
                }
            }, function(err) {
                if (typeof onRejected === 'function') {
                    try {
                        resolve(onRejected(err));
                    } catch (e) {
                        reject(e)
                    }
                } catch (e) {
                    return reject(err)
                }
            })
        })
    }


    doResolve(fn, resolve, reject);
}

function doResolve(fn, onFulfilled, onRejected) {
    let done = false;
    try {
        fn(function(value) {
            if (done === true) {
                return;
            }
            done === true;
            onFulfilled(value);
        }, function(err) {
            if (done === true) {
                return;
            }
            done === true;
            onRejected(err);
        });
    } catch (e) {
        if (done === true) return
        done = true
        onRejected(e);
    }
}

function getThen(obj) {
    if (typeof obj === 'object' || typeof obj === 'function') {
        var then = obj.then;
        if (typeof then === 'function') {
            return then;
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