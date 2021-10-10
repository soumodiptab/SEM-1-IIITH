function delay(t, i, state=true){
    return new Promise((resolve, reject) => {
        if (state)
            setTimeout(() => {resolve("resolved " + i)}, t);
        else
            setTimeout(() => {reject("rejected " + i)}, t);
    })
}

let p1 = delay(1000, 1);
let p2 = delay(2000, 2);
let p3 = delay(3000, 3);

// Promise.all([p1, p2, p3]).then((values) => {console.log(values)}).catch(err => console.log(err))

Promise.any([p1, p2, p3]).then((value) => {console.log(value)}).catch(err => console.log(err))