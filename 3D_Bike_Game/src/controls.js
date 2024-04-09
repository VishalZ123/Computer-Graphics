import * as THREE from "three";
import { playerBikeConfig } from "./configs";

import {
  maxSpeedForward,
  moveSpeedForward,
  moveSpeedBackward,
  rotationSpeed,
  maxSpeedBackward,
  mileage
} from "./constants";

let speed = 0;
let fuel = 1;

// Variables to track movement in each direction
let moveForward = false;
let moveBackward = false;
let moveLeft = false;
let moveRight = false;

function setSpeed(newSpeed) {
  speed = newSpeed;
}

function setFuel(newFuel) {
  fuel = newFuel;
}

function getFuel() {
  return fuel;
}

// Add event listeners for keyboard inputs
document.addEventListener("keydown", (event) => {
  switch (event.code) {
    case "KeyW":
      moveForward = true;
      break;
    case "KeyS":
      moveBackward = true;
      break;
    case "KeyA":
      moveLeft = true;
      break;
    case "KeyD":
      moveRight = true;
      break;
    case "ArrowUp":
      moveForward = true;
      break;
    case "ArrowDown":
      moveBackward = true;
      break;
    case "ArrowLeft":
      moveLeft = true;
      break;
    case "ArrowRight":
      moveRight = true;
      break;
  }
});

document.addEventListener("keyup", (event) => {
  switch (event.code) {
    case "KeyW":
      moveForward = false;
      break;
    case "KeyS":
      moveBackward = false;
      break;
    case "KeyA":
      moveLeft = false;
      break;
    case "KeyD":
      moveRight = false;
      break;
    case "ArrowUp":
      moveForward = false;
      break;
    case "ArrowDown":
      moveBackward = false;
      break;
    case "ArrowLeft":
      moveLeft = false;
      break;
    case "ArrowRight":
      moveRight = false;
      break;
  }
});

function updateBikePosition(camera) {
  const direction = new THREE.Vector3(0, 0, 1);
  direction.applyEuler(playerBikeConfig.rotation);

  const perpendicularDirection = new THREE.Vector3();
  perpendicularDirection.crossVectors(direction, camera.up);

  if (moveForward) {
    speed = Math.min(speed + moveSpeedForward, maxSpeedForward);
    fuel -= speed / mileage;
    document.querySelector("#fuel-length").style.width =
      Math.max(fuel * 150, 0) + "px";
  } else if (moveBackward) {
    speed = Math.max(speed - moveSpeedBackward, maxSpeedBackward);
  } else {
    speed = Math.sign(speed) * Math.max(0, Math.abs(speed) - moveSpeedForward);
  }

  playerBikeConfig.position.addScaledVector(direction, -speed);
  camera.position.addScaledVector(direction, -speed);

  if (moveLeft) {
    playerBikeConfig.rotation.y += rotationSpeed;
    camera.position.addScaledVector(
      perpendicularDirection,
      -1.5 * rotationSpeed
    );
  }

  if (moveRight) {
    playerBikeConfig.rotation.y -= rotationSpeed;
    camera.position.addScaledVector(
      perpendicularDirection,
      1.5 * rotationSpeed
    );
  }
}

export { updateBikePosition, setSpeed, setFuel, getFuel };
