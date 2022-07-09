// Expressions in the type system.

export class Lambda {
  kind: 'lambda';
  domain: Expr;
  value: Expr;
}

export class Pi {
  kind: 'pi';
  domain: Expr;
  value: Expr;
}

export class Application {
  kind: 'app';
  function: Expr;
  argument: Expr;
}

export class Variable {
  kind: 'var';
  name: String;

  constructor(_name: String) {
    this.name = _name;
  }
}

export type Expr = Lambda | Pi | Application | Variable;

// The statement that the object `x` has type `A`.
class TypeDeclaration {
  x: String;
  A: Expr;
}

// An environment is a list of type declarations.
class Environment {
  declarations: TypeDeclaration[];

  constructor(_declarations: TypeDeclaration[]) {
    this.declarations = _declarations;
  }

  // The empty environment, with no declarations.
  static empty(): Environment {
    return new Environment([]);
  }

  // Creates a new environment by adding a declaration to a previous one.
  static add(env: Environment, decl: TypeDeclaration): Environment {
    let newDecls = [...env.declarations];
    newDecls.push(decl);
    return new Environment(newDecls);
  }

  // Whether a string is not used in a declaration.
  nameFree(name: String): Boolean {
    for (let decl of this.declarations) {
      if (decl.x === name)
        return false;
    }
    return true;
  }

  // Returns a declaration if it exists.
  getDeclaration(name: String): TypeDeclaration | undefined {
    for (let decl of this.declarations) {
      if (decl.x === name)
        return decl;
    }
    return undefined;
  }
}


// Judgments within the type theory.

// The environment `env` is a well-formed context.
class ContextJudgment {
  env: Environment;

  constructor(_env: Environment) {
    this.env = _env;
  }
}

// The expression `x` has the type `A` in the environment `env`.
class TypeJudgment {
  env: Environment;
  x: Expr;
  A: Expr;

  constructor(_env: Environment, _x: Expr, _A: Expr) {
    this.env = _env;
    this.x = _x;
    this.A = _A;
  }
}

// The expressions `x` and `y` are definitionally equal as members of `A` in the environment `env`.
class EqJudgment {
  env: Environment;
  x: Expr;
  y: Expr;
  A: Expr;

  constructor(_env: Environment, _x: Expr, _y: Expr, _A: Expr) {
    this.env = _env;
    this.x = _x;
    this.y = _y;
    this.A = _A;
  }
}


// Rules of inference.

// The empty environment is well-formed.
function contextEmpty(): ContextJudgment {
  return new ContextJudgment(Environment.empty());
}

// TODO: Context extension.

// If an environment postulates a variable of some type, it follows that the
// variable has this type in this context.
function contextVariable(env: Environment, name: String): TypeJudgment | undefined {
  let decl = env.getDeclaration(name);
  if (typeof decl === 'undefined') {
    return undefined;
  } else {
    return new TypeJudgment(env, new Variable(decl.x), decl.A);
  }
}

// Reflexivity for definitional equality.
function eqReflexive(judg: TypeJudgment): EqJudgment {
  return new EqJudgment(judg.env, judg.x, judg.x, judg.A);
}

// Symmetry for definitional equality.
function eqSymmetric(judg: EqJudgment): EqJudgment {
  return new EqJudgment(judg.env, judg.y, judg.x, judg.A);
}

// Transitivity for definitional equality.
function eqTransitive(judg1: EqJudgment, judg2: EqJudgment): EqJudgment | undefined {
  if (judg1.env != judg2.env) {
    return undefined;
  } else if (judg1.A != judg2.A) {
    return undefined;
  } else if (judg1.y != judg2.x) {
    return undefined;
  } else {
    return new EqJudgment(judg1.env, judg1.x, judg2.y, judg1.A);
  }
}

// Transport of type judgments using definitional equality.
function typeTransport(j1: TypeJudgment, j2: EqJudgment): TypeJudgment | undefined {
  if (j1.env != j2.env) {
    return undefined;
  } else if (j1.A != j2.x) {
    return undefined;
  } else {
    return new TypeJudgment(j1.env, j1.x, j2.y);
  }
}

// Transport of definitional equality using definitional equality.
function eqTransport(j1: EqJudgment, j2: EqJudgment): EqJudgment | undefined {
  if (j1.env != j2.env) {
    return undefined;
  } else if (j1.A != j2.x) {
    return undefined;
  } else {
    return new EqJudgment(j1.env, j1.x, j1.y, j2.y);
  }
}