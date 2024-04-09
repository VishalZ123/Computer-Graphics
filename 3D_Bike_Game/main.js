import * as THREE from "three";
import { RGBELoader } from "three/addons/loaders/RGBELoader.js";
import { GroundedSkybox } from "three/addons/objects/GroundedSkybox.js";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { loadObject } from "./src/loadObjects.js";
import {
  trackConfig,
  playerBikeConfig,
  resetConfig,
  fuelCanLocations
} from "./src/configs.js";
import {
  updateBikePosition,
  setSpeed,
  setFuel,
  getFuel
} from "./src/controls.js";
import { addLights } from "./src/addLights.js";
import { changeState, gameState } from "./src/game.js";
import {
  GAME_START,
  GAME_PLAY,
  GAME_OVER,
  GAME_WIN,
  GAME_PAUSE
} from "./src/constants";

const scene = new THREE.Scene();
const app = document.querySelector("#app");

const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setPixelRatio(window.devicePixelRatio);
renderer.setSize(app.offsetWidth, app.offsetHeight);
app.appendChild(renderer.domElement);

// camera
const camera = new THREE.PerspectiveCamera(
  75,
  app.offsetWidth / app.offsetHeight,
  0.1,
  1000
);

camera.position.set(26.1, 0.5, 13);
camera.lookAt(playerBikeConfig.position);

// apply environment map from .hdr file
const hdrLoader = new RGBELoader();
const envMap = await hdrLoader.loadAsync("assets/textures/envmap.hdr");
envMap.mapping = THREE.EquirectangularReflectionMapping;
scene.environment = envMap;
const params = {
  height: 15,
  radius: 100,
  enabled: true
};
let skybox = new GroundedSkybox(envMap, params.height, params.radius);
skybox.position.y = params.height - 0.01;
scene.add(skybox);

addLights(scene);

// load the track model
loadObject("./assets/models/race_track.fbx", scene, trackConfig);

// load the bike model
loadObject(
  "./assets/models/suzuki_gsx_750_bike_3d_model.glb",
  scene,
  playerBikeConfig,
  (model, config) => {
    model.position.x = playerBikeConfig.position.x;
    model.position.y = playerBikeConfig.position.y;
    model.position.z = playerBikeConfig.position.z;
    model.rotation.y = playerBikeConfig.rotation.y;
  }
);

// load bike model from obj file
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
var opponents = [];
const gltfLoader = new GLTFLoader();
gltfLoader.load("./assets/models/suzuki_gsx_750_bike_3d_model.glb", (model) => {
  model.scene.scale.set(0.2, 0.2, 0.2);
  model.scene.position.set(27.6, 0, 13.2);
  model.scene.rotation.set(0, -1.278, 0);
  // give the bike a random color
  let randomColor = Math.random() * 0xffffff;
  model.scene.traverse((child) => {
    if (child.isMesh) {
      child.material.color.setHex(randomColor);
    }
  });
  opponents.push(model.scene);
  opponents.push(model.scene.clone());
  opponents.push(model.scene.clone());
  opponents[1].position.set(27.4, 0, 12.2);
  opponents[2].position.set(27.3, 0, 11.8);
  opponents.forEach((opponent) => {
    scene.add(opponent);
  });
});

function drawFuelCans() {
  fuelCanLocations.forEach((config) => {
    loadObject(
      "./assets/models/fuelcan.glb",
      scene,
      config,
      (model, config) => {
        // if the distance between the bike and the fuel can is less than 0.2
        // then the fuel can is collected
        if (
          Math.sqrt(
            Math.pow(playerBikeConfig.position.x - config.position.x, 2) +
              Math.pow(playerBikeConfig.position.z - config.position.z, 2)
          ) < 0.2
        ) {
          if (config.used) return;
          setFuel(1);
          model.visible = false;
          config.used = true;
        }
      }
    );
  });
}

drawFuelCans();

// a textured plane
const planeGeometry = new THREE.PlaneGeometry(5, 2);
const textureLoader = new THREE.TextureLoader();
const texture = textureLoader.load("./assets/textures/crowd.jpg");
texture.wrapS = THREE.RepeatWrapping;
texture.wrapT = THREE.RepeatWrapping;
texture.repeat.set(2.5, 2);

const planeMaterial = new THREE.MeshStandardMaterial({
  map: texture,
  side: THREE.DoubleSide
});
const plane = new THREE.Mesh(planeGeometry, planeMaterial);
plane.rotation.x = -1;
plane.position.set(27.6, 0.7, 9.7);
scene.add(plane);

// controls
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

var t = 0;
var health = 1;
import { paths } from "./src/paths.js";
var c = [0, 0, 0];
function animate() {
  requestAnimationFrame(animate);
  controls.update();
  if (getFuel() <= 0) {
    changeState(GAME_OVER);
  }
  if (gameState === GAME_PLAY) {
    t += 1 / 60;
    document.querySelector("#time").innerText = `Time : ${t.toFixed(2)}`;
    updateBikePosition(camera);
    for (let i = 0; i < paths.length; i++) {
      if (c[i] < paths[i].length) {
        opponents[i].rotation.set(
          paths[i][c[i]].rotation._x,
          paths[i][c[i]].rotation._y,
          paths[i][c[i]].rotation._z
        );
        opponents[i].position.set(
          paths[i][c[i]].position.x,
          paths[i][c[i]].position.y,
          paths[i][c[i]].position.z
        );
      }
      c[i]++;
    }
    // check collision with any of the opponents
    for (let i = 0; i < opponents.length; i++) {
      if (
        Math.sqrt(
          Math.pow(playerBikeConfig.position.x - opponents[i].position.x, 2) +
            Math.pow(playerBikeConfig.position.z - opponents[i].position.z, 2)
        ) < 0.1
      ) {
        health -= 0.1;
        document.querySelector("#health-length").style.width =
          Math.max(health * 150, 0) + "px";
        if (health <= 0) {
          changeState(GAME_OVER);
        }
      }
    }
  }
  camera.lookAt(playerBikeConfig.position);
  renderer.render(scene, camera);
}

animate();

// add eventlistener to change the game state
function handleKeyDown(event) {
  if (event.key === " ") {
    if (gameState === GAME_START) {
      changeState(GAME_PLAY);
    } else if (gameState === GAME_PLAY) {
      changeState(GAME_PAUSE);
    } else if (gameState === GAME_PAUSE) {
      changeState(GAME_PLAY);
    }
  } else if (event.key === "r") {
    if (
      gameState === GAME_PAUSE ||
      gameState === GAME_OVER ||
      gameState === GAME_WIN
    ) {
      changeState(GAME_START);
      t = 0;
      document.querySelector("#time").innerText = `Time : 0.00`;
      // reset the bike position
      playerBikeConfig.position.copy(resetConfig.bike.position);
      playerBikeConfig.rotation.copy(resetConfig.bike.rotation);
      camera.position.set(
        resetConfig.camera.position.x,
        resetConfig.camera.position.y,
        resetConfig.camera.position.z
      );
      camera.lookAt(playerBikeConfig.position);
      setSpeed(0);
      setFuel(1);
      c = [0, 0, 0];
      document.querySelector("#fuel-length").style.width = "150px";
      document.querySelector("#health-length").style.width = "150px";
      fuelCanLocations.forEach((config) => {
        config.used = false;
      });
      drawFuelCans();
    }
  } else if (event.key === "t") {
    // toggle camera view
    console.log(camera.position.y);
    camera.position.y = Math.abs(camera.position.y - 0.5) < 0.01 ? 5 : 0.5;
  }
}
document.addEventListener("keydown", handleKeyDown);
