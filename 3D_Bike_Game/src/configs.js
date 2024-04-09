import * as THREE from "three";

const resetConfig = {
  bike: {
    position: new THREE.Vector3(27.6, 0, 12.6),
    rotation: new THREE.Euler(0, -1.278, 0),
    scale: new THREE.Vector3(0.2, 0.2, 0.2)
  },
  camera: {
    position: new THREE.Vector3(26.1, 0.5, 13)
  }
};
const trackConfig = {
  position: new THREE.Vector3(0, 0, 0),
  rotation: new THREE.Euler(0, 0, 0),
  scale: new THREE.Vector3(1, 1.5, 1)
};

const playerBikeConfig = {
  position: new THREE.Vector3(27.6, 0, 12.6),
  rotation: new THREE.Euler(0, -1.278, 0),
  scale: new THREE.Vector3(0.2, 0.2, 0.2)
};

const fuelCanLocations = [
  {
    position: new THREE.Vector3(44, 0.1, -17.08),
    rotation: new THREE.Euler(0, 0, 0),
    scale: new THREE.Vector3(0.1, 0.1, 0.1),
    used: false
  },
  {
    position: new THREE.Vector3(19.46, 0.1, -12.55),
    rotation: new THREE.Euler(0, 0, 0),
    scale: new THREE.Vector3(0.1, 0.1, 0.1),
    used: false

  },
  {
    position: new THREE.Vector3(-25.43, 0.1, -4.47),
    rotation: new THREE.Euler(0, 0, 0),
    scale: new THREE.Vector3(0.1, 0.1, 0.1),
    used: false
  },
  {
    position: new THREE.Vector3(-17.14, 0.1, 6.88),
    rotation: new THREE.Euler(0, 0, 0),
    scale: new THREE.Vector3(0.1, 0.1, 0.1),
    used: false
  },
  {
    position: new THREE.Vector3(14.83, 0.1, 13.6),
    rotation: new THREE.Euler(0, 0, 0),
    scale: new THREE.Vector3(0.1, 0.1, 0.1),
    used: false
  }
];

export { resetConfig, trackConfig, playerBikeConfig, fuelCanLocations };
