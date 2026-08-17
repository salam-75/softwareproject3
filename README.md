# CSE 3206: Software Engineering Sessional
## Lab 3: Design Pattern Analysis, Implementation, and Code Review
**Institution:** Rajshahi University of Engineering & Technology (RUET)  
**Department:** Computer Science & Engineering  
**Group:** 05  
**Assigned Patterns:** Flyweight Pattern & Proxy Pattern  

---

## Part 1: Flyweight Design Pattern

### 1. Pattern Name
* Flyweight Pattern

### 2. Category
* Structural Design Pattern

### 3. Intent
* To minimize memory usage by sharing as much data as possible with other similar objects.

### 4. Problem Statement
* When an application needs to create a huge number of similar objects (e.g., thousands of trees in a game map or characters in a text editor), the system may crash due to high memory consumption (Out of Memory).

### 5. Motivation
* Instead of storing identical data (Intrinsic State) repeatedly inside every single object, we extract it. We share this common data among multiple objects, storing only the unique data (Extrinsic State) separately. This drastically reduces the memory footprint compared to normal object creation.

### 6. Pattern Structure (UML Concept)
```text
[ Client ] 
   │
   ▼
[ FlyweightFactory ] ─── Gives ───► [ Flyweight (Interface) ]
   │                                         ▲
   ▼ (Manages Shared States)                 │ (Implements)
[ Shared Intrinsic State ]          [ ConcreteFlyweight ]
```

### 7. Class Responsibilities
* **Flyweight Interface:** Declares methods through which flyweights can receive and act on extrinsic states.
* **ConcreteFlyweight:** Stores intrinsic state that is shareable and independent of the context.
* **FlyweightFactory:** Creates and manages flyweight objects, ensuring they are shared properly.
* **Client:** Computes or stores the extrinsic state and passes it to the flyweight.

### 8. Code Implementation (C++)
The code can be found inside the `/Code/flyweight_pattern.cpp` file.

### 9. Execution Flow
1. Client requests a flyweight object from `FlyweightFactory`.
2. Factory checks if it already exists; if yes, it returns the existing one; if no, it creates a new one.
3. Client passes the unique extrinsic context (like X, Y coordinates) to the shared flyweight object's method during execution.

### 10. Advantages
* Reduces memory usage exponentially.
* Lowers total number of active objects in the system.

### 11. Limitations
* Increases runtime complexity due to separating intrinsic and extrinsic states.
* Requires extra time to look up shared objects via the factory.

### 12. Real-life Applications
* Word Processors (sharing character formatting details like Font Name, Style, Color).
* Graphic rendering engines (drawing thousands of identical trees, bullets, or particles).

### 13. Industry Examples
* Java's `String` Pool and `Integer.valueOf()` caching mechanism.
* Game development engines like Unity or Unreal Engine for object instancing.

---

## Part 2: Proxy Design Pattern

### 1. Pattern Name
* Proxy Pattern

### 2. Category
* Structural Design Pattern

### 3. Intent
* To provide a placeholder or surrogate object for another object to control access to it.

### 4. Problem Statement
* Accessing a resource-heavy or sensitive object directly can cause slow application startups, security risks, or unnecessary resource allocation when the object isn't actually being used.

### 5. Motivation
* A normal direct implementation instantiates huge resources immediately. A Proxy pattern acts as an intermediary. It can delay the expensive initialization (Lazy Loading), check access permissions (Protection Proxy), or log activities before hitting the real object.

### 6. Pattern Structure (UML Concept)
```text
                [ Subject (Interface) ]
                         ▲
            ┌────────────┴────────────┐
            │                         │
     [ RealSubject ] ◄───Calls─── [ Proxy ]
                                      ▲
                                      │
                                  [ Client ]
```

### 7. Class Responsibilities
* **Subject Interface:** Defines a common interface so that the Proxy can be used anywhere the RealSubject is expected.
* **RealSubject:** The actual heavy/sensitive object that performs the core business logic.
* **Proxy:** Maintains a reference to the RealSubject, controls access to it, and matches the Subject interface.
* **Client:** Interacts with the Proxy instead of calling the RealSubject directly.

### 8. Code Implementation (C++)
The code can be found inside the `/Code/proxy_pattern.cpp` file.

### 9. Execution Flow
1. Client calls a method on the Proxy object.
2. Proxy executes its internal logic (e.g., authorization check, lazy initialization).
3. Proxy passes the request to the `RealSubject` instance if conditions are met.

### 10. Advantages
* Implements Security/Access Control seamlessly.
* Increases efficiency through Lazy Loading (Virtual Proxy).
* Works without needing modifications to the original heavy object.

### 11. Limitations
* Introduces an extra layer of abstraction which might slightly delay responses.
* Complicates the codebase structure with extra proxy classes.

### 12. Real-life Applications
* Credit Cards (acting as a proxy for the actual cash in a bank account).
* Internet Firewall/Cache servers (restricting or fast-tracking web access).

### 13. Industry Examples
* Hibernate (Java Framework) uses proxies for lazy-loading database relations.
* Remote Method Invocation (RMI) or RPC stubs in distributed systems.

---

## Part 3: Code Review Checklist
* [x] **Naming Conventions:** Descriptive names used for classes, variables, and methods.
* [x] **SOLID Principles:** Single Responsibility Principle followed via structural separation.
* [x] **Readability & Formatting:** Properly indented code with comments.
* [x] **Exception Handling:** Guard clauses included for safe edge-case executions.
