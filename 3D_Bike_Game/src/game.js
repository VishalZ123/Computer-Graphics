import {
  GAME_START,
  GAME_PLAY,
  GAME_OVER,
  GAME_WIN,
  GAME_PAUSE
} from "./constants";

var gameState = GAME_START;

const startDashboard = document.querySelector("#start-screen");
const pauseDashboard = document.querySelector("#pause-screen");
const gameOverDashboard = document.querySelector("#game-over-screen");
const gameWinDashboard = document.querySelector("#game-win-screen");

if (gameState === GAME_START) {
  startDashboard.style.visibility = "visible";
  startDashboard.querySelector("#game-state").style.color = "green";
}

function changeState(state) {
  gameState = state;
  // change the text content based on the game state
  if (gameState === GAME_START) {
    pauseDashboard.style.visibility = "hidden";
    gameOverDashboard.style.visibility = "hidden";
    gameWinDashboard.style.visibility = "hidden";
    startDashboard.style.visibility = "visible";
    startDashboard.querySelector("#game-state").style.color = "green";
  }
  if (gameState === GAME_PLAY) {
    startDashboard.style.visibility = "hidden";
    pauseDashboard.style.visibility = "hidden";
    gameOverDashboard.style.visibility = "hidden";
    gameWinDashboard.style.visibility = "hidden";
  } else if (gameState === GAME_PAUSE) {
    pauseDashboard.style.visibility = "visible";
    pauseDashboard.querySelector("#game-state").style.color = "blue";
  } else if (gameState === GAME_OVER) {
    gameOverDashboard.style.visibility = "visible";
    gameOverDashboard.querySelector("#game-state").style.color = "red";
  } else if (gameState === GAME_WIN) {
    gameWinDashboard.style.visibility = "visible";
    gameWinDashboard.querySelector("#game-state").style.color = "yellow";
  }
}

export { gameState, changeState };
