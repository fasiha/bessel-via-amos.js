export = enhancedModulePromise;

declare const enhancedModulePromise: Promise<MyObject>;

interface MyObject {
  kv: (nu: number, z: number) => number;
  kve: (nu: number, z: number) => number;
}