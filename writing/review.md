Here I am collecting my (opinionated!) thoughts on other proof checkers and libraries of formalized proofs in an attempt to clarify my understanding of them and craft a proposal to improve upon them.

# Impressions of Existing Proof Checkers/Assistants
## [Metamath](http://us.metamath.org/) / [`set.mm`](http://us.metamath.org/mpeuni/mmset.html)
### The Good
- The inner workings of Metamath are easy to understand. The Metamath system has a few simple rules, which allow you to construct systems like ZFC within it.
- Metamath is really fast. You can verify everything in `set.mm` in less than a minute.
### The Bad
- You have to do *everything* in Metamath. I have heard Metamath called the "assembly language of logic", and this is pretty much true. While this is part of the design philosophy of Metamath, it makes it unappealing for serious formalization, because proving things in axiomatic propositional calculus gets really boring really quickly.
- Metamath does not really have a computational/programming aspect.
- There is essentially zero structure for organizing libraries. Everything is combined into a single gigantic file.
- The documentation for proofs is poor. There is essentially no explanation of the proofs in natural language to accompany the formalized proofs.

## [Lean](https://leanprover.github.io/) / [mathlib](https://leanprover-community.github.io/index.html)
### The Good
- The type theory of Lean is very comfortable for doing mathematics. Using propositions-as-types takes a *little* getting used to, but is easy and natural. Inductive types and quotient types make essentially all constructions in mathematics possible and easy to formalize.
- Lean can be used naturally for programming.
- Libraries can be organized nicely within Lean using directories, files, and imports.
- The library mathlib has a significant chunk of basic mathematics formalized.
### The Bad
- Lean is prohibitively slow. Checking mathlib from scratch is essentially impossible to do without a beefy computer, and even then, it can take hours and consume all 16GB of your memory. It seems as though there is some kind of major flaw in the implementation. In principle, we should be able to download the artifacts from the checker built online to avoid checking the entire library from scratch, but even checking modifications made to a single file is frustratingly sluggish.
- In mathlib, basic definitions are written as special cases of more abstract and complex definitions. For example, [binary products](https://leanprover-community.github.io/mathlib_docs/category_theory/limits/shapes/binary_products.html#category_theory.limits.has_binary_products) in a category are defined as limits of a certain shape. While this definition is correct, it is unnecessarily complicated. Defining a binary product as a limit makes it less accessible to those who might know about products in a category, but not general limits. This also has the problem that a definition may be a special case or example of multiple abstractions, and it is not clear which to use, or it requires updating the definition to be even more abstract. It would be better to define a product as an object with projections that is universal with respect to this property, and then *prove* that a product is a special case of a limit.
- The elaborator can be frustrating to work with. It is often the case that the elaborator cannot guess whatever you are trying to express, so you need to resort to explicitly supplying *all* the arguments.
- The elaborator and tactics are essentially black boxes. They take a long time to run to generate terms/proofs that you never really see. It would be better to use some kind of meta-functions that explicitly state (and prove!) how they manipulate terms and proofs.
- It is not clear how to do programming in a more "general" way. Ideally Lean is not just a programming language, but a system for constructing formally verified programs and software in the most general way possible, including the use of other languages.
- Lean relies heavily on unicode characters in its source files. This makes VS Code the only editor suitable for editing Lean files, since it is the only editor with an extensive Lean extension.
- There is little structure for organizing multiple projects in relation to each other, so everything must be incorporated into mathlib.
- The documentation for proofs in mathlib is poor. There is essentially no explanation of the proofs in natural language to accompany the formalized proofs.

## Summary
Both Metamath and Lean do a few things well:
- Correctness and expressiveness.
- Lean has convenient foundations.
- Metamath is easy to understand.
- Mathlib has accomplished a lot.

But there are major problems that make both of them inconvenient for formalizing difficult mathematics:
- Poor performance.
- Extreme transparency in the case of Metamath, or too many black boxes with unreliable behavior in the case of Lean.
- Lack of structure for effectively organizing bodies of formalized mathematics.
- No "unified" programming.

Their "standard libraries" `set.mm` and mathlib also have issues:
- Poor documentation of formalized math.
- Abstraction is handled incorrectly.

There is one final major issue that applies to both on a larger scale: they cannot talk to each other!

# The Ideal Proof Checker/Assistant
With the above critique of Metamath and Lean in mind, we will now describe an "ideal" proof assistant that addresses these shortcomings. We want it to have the following features (in order from most to least important):
- Correctness.
- Expressiveness.
- Performance: Low memory usage and speed.
- Convenient foundations: It should not take a lot of effort to express what we want to say. We should not have to prove thousands of theorems about propositional calculus.
- Modularity: Instead of forcing "monolith" libraries like `set.mm` and mathlib, there should be a convenient way of separating and managing libraries with dependencies. It should also be possible to export modules to something other proof assistants can use, and import libraries from other proof assistants as modules.
- Documentation: Documentation in natural language should be easy and generate nice looking, convenient resources like [Stacks](https://stacks.math.columbia.edu/) and [Kerodon](https://kerodon.net/).
- First-Class Programming: Using type theory, proofs and definitions have computational content coming from the reduction of terms. Computational aspects of the system, such as programs manipulating the logical environment and synthesizing proofs or terms, should be incorporated into the computational interpretation of the type theory. We should additionally be able to construct and interact with arbitrary programs, proving statements about them. Note that we should be able to work with programming at the level of machine code or at the level of type theory, proving that the code has the expected properties.
- Customizability: The syntax and notation of the system should be entirely customizable, to the point that a parser for the desired syntax can be written within the system and used for constructing terms. For example, when working with associative algebraic structures, we can avoid bracketing when unnecessary and use a custom parser to put expressions into a normal form.
- No Black Boxes: Avoid structures like an elaborator, which behaves like a black box in most scenarios. Unless you are familiar with how the elaborator works, you are subject to its quirks and shortcomings. It is better to use a more verbose, but transparent (and formally verified) mechanism for filling in gaps.

Modules should have the following properties:
- Purpose: A module should have a well-defined purpose that is limited in scope and achievable, such as formalizing a textbook or paper, a software library, or a program.
- Organization: Modules should be organized in a logical fashion that makes them easy to inspect and modify.
- Documentation: Every module should have clear, extensive documentation in natural language with plenty of exposition and references.
- Abstraction: Instead of expressing definitions as special cases of the most general, abstract case, define them concretely and then *prove* that they are special cases of the general picture.

# The Proposal
**Fibrant** is a proof assistant intended to satisfy all these criteria. An implementation of Fibrant consists (roughly) of the following things:
- A type checker.
- An interpreter for the Fibrant language.
- A command-line interface for managing modules.

We will now describe these three components in detail.

## The Type Checker
For the foundations of Fibrant, we go with a type theory due to its convenience and natural computational connection. While there are many options for type theories, we need dependent types and inductive types in order for the system to be expressive and convenient enough for mathematics. Without explicitly constructing a new type theory, which is out of my expertise, we can choose among the typing systems already used in some proof assistants. The two main contenders are the type theory of Lean, and cubical type theory. I would like to go with cubical type theory, but it is quite complicated and I would like this system to be accessible to as many people as possible. Therefore the type theory of Fibrant is actually just the type theory of Lean.

## The Language
While Fibrant is intended to allow users to define their own language to best suit their purposes, a simple but powerful language is necessary to get started. The basic language is called **Lift**, and the file extension is `.lft`. A Lift file is just a sequence of **statements**. There are a few kinds of statements:
- Import statements: The syntax of import statements in Lift is borrowed from [Python](https://docs.python.org/3/reference/simple_stmts.html#import), with roughly the same semantics.
- Definitions:
- Axioms:
- Inductive Types:

To every statement can be attached documentation.

There are various kinds of expressions:
- Interpolation Expressions: Users can define custom languages and embed them directly into Lift source files between special delimiters.

In addition to the core language, we make available a library allowing one to interact with the system itself. This is similar to reflection, but more "universe-y". Every Lift interpreter supplies a module that allows one to instantiate a new instance of the interpreter and manipulate it.

## The Interface
Finally, we describe the module interface. A **Fibrant module**, or **Fiber**, is a directory containing a `fiber.json` file. The `fiber.json` file should contain a single JSON object, structured as follows:
```
Fiber {
  "name": String,
  "description": String,
  "version": String,
  "authors": [Author],
  "license": String,
  "scripts": [Script],
  "dependencies": [Dependency]
}
```

```
Author {
  "name": String,
  "email"?: String,
  "website"?: String,
  "organization"?: String
}
```

```
Script {
  "name": String,
  "path": String
}
```

```
Dependency {
  "name": String,
  "version": String
}
```

The command line utility should have general commands for manipulating and installing modules, similar to `cargo` and `npm`.

