import * as THREE from "three";
import { FBXLoader } from "three/examples/jsm/loaders/FBXLoader.js";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";

function animateModel(model, config, updateFunction) {
  function animate() {
    requestAnimationFrame(animate);
    updateFunction(model, config);
  }

  animate();
}

function loadFBX(path, scene, config) {
  const loader = new FBXLoader();
  loader.load(path, (fbx) => {
    fbx.traverse((child) => {
      if (child.isMesh) {
        const name = child.name;
        const materials = child.material;

        switch (name) {
          case "land":
            const texture = materials.map;
            child.material = new THREE.MeshLambertMaterial({
              map: texture
            });
            break;
          case "banner":
            for (let i = 0, l = materials.length; i < l; i++) {
              const texture = materials[i].map;
              materials[i] = new THREE.MeshLambertMaterial({ map: texture });
            }
            break;
        }
        child.castShadow = true;
        child.receiveShadow = true;
      }
    });

    scene.add(fbx);

    // Adjusting the position, rotation, scale if needed
    fbx.position.set(config.position.x, config.position.y, config.position.z);
    fbx.rotation.set(config.rotation.x, config.rotation.y, config.rotation.z);
    fbx.scale.set(config.scale.x, config.scale.y, config.scale.z);
  });
}

function loadGLB(path, scene, config, updateFunction) {
  const loader = new GLTFLoader();
  loader.load(
    path,
    (gltf) => {
      // Adjusting the position, rotation, scale if needed
      gltf.scene.position.set(
        config.position.x,
        config.position.y,
        config.position.z
      );
      gltf.scene.rotation.set(
        config.rotation.x,
        config.rotation.y,
        config.rotation.z
      );
      gltf.scene.scale.set(config.scale.x, config.scale.y, config.scale.z);
      scene.add(gltf.scene);
      if (updateFunction) {
        animateModel(gltf.scene, config, updateFunction);
      }
    },
    undefined,
    (error) => {
      console.error("Error loading glTF model", error);
    }
  );
}

function loadObject(path, scene, config, callback) {
  // check the file extension
  if (path.endsWith(".fbx")) {
    loadFBX(path, scene, config);
  } else if (path.endsWith(".glb")) {
    loadGLB(path, scene, config, callback);
  }
}

export { loadObject };
