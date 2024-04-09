import * as THREE from "three";

function addLights(scene){
    
    // add an ambient light
    const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
    scene.add(ambientLight);
}

export { addLights };