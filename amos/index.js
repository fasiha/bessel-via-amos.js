const ModulePromise = require('./a.out.js')();

const enhancedModulePromise = ModulePromise.then((resolvedModule) => {
  resolvedModule.kv = resolvedModule._kv;
  resolvedModule.kve = resolvedModule._kve;
  return resolvedModule;
})

module.exports = enhancedModulePromise;