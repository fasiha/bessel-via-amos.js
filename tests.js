const amosPromise = require('./index');

function relativeError(actual, expected) {
  return Math.abs((actual - expected) / expected);
}

amosPromise.then(amos => {
  const errs = []
  errs.push(relativeError(amos.kve(4.4, 3.3), 7.44311267732952));
  errs.push(relativeError(amos.kv(4.4, 3.3), 0.27452557086423646));
  if (errs.some(err => err > 2.3e-15)) {
    throw new Error('error exceeded machine tolerance')
  }
})