var t = 0;

function getTime(){
    return t;
}

function resetTimer(){
    t = 0;
}

function updateTimer(){
    t += 1 / 60;
    document.querySelector("#time").innerText = `Time : ${t.toFixed(2)}`;
}

export { getTime, resetTimer, updateTimer };