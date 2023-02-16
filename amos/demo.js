var modulePromise = require('./index');
modulePromise.then(module => {
  console.log(module.kve(4.4, 3.3));
})