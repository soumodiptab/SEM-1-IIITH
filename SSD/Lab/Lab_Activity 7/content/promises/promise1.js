// Callback hell

// setTimeout(function(){
//     console.log("Level 1");
//     setTimeout(function(){
//         console.log("Level 2");
//         setTimeout(function(){
//             console.log("Level 3");
//         }, 800)
//     }, 500)
// }, 1000);


// Promises

function delay(t, i, state=true){
    return new Promise((resolve, reject) => {
        console.log("Level " + i)
        if (state)
            setTimeout(resolve, t);
        else
            setTimeout(reject, t);
    })
}

delay(1000, 1).then(() => {
    return delay(500, 2);
}).then(() => {
    return delay(800, 3, false);
}).catch(err => {
    console.log("Error thrown");
})