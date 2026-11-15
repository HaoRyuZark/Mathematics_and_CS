# Analysis I – Übungsblatt 4: Solutions

**Conventions.** $\mathbb N=\{1,2,3,\dots\}$, $\mathbb N_0=\mathbb N\cup\{0\}$. Finite sums are defined recursively for $l\le m$:

$$
\sum_{j=l}^{l} a_j := a_l,\qquad \sum_{j=l}^{m+1} a_j := \sum_{j=l}^{m} a_j + a_{m+1}.
$$

(Products work the same way.) Only elementary facts are used: field axioms, order axioms, induction, and basic facts about $\mathbb N$ and $\mathbb Z$ (for example, there is no integer strictly between $n$ and $n+1$).

---

## Aufgabe 1 (Strong induction)

**Claim.** Let $n_0\in\mathbb Z$ and suppose
- (sIA) $A(n_0)$ is true, and
- (sIS) for all $n\ge n_0$: if $A(n_0),\dots,A(n)$ are true, then $A(n+1)$ is true.

Then $A(n)$ is true for all $n\ge n_0$.

**Proof.** For $n\ge n_0$, define the auxiliary statement

$$
B(n):\quad A(k)\ \text{is true for all } k\in\mathbb Z \text{ with } n_0\le k\le n .
$$

We prove $B(n)$ for all $n\ge n_0$ by **ordinary** induction.

*Base case ($n=n_0$).* $B(n_0)$ says exactly that $A(n_0)$ is true. This holds by (sIA).

*Induction step ($n\to n+1$).* Assume $B(n)$ holds for some $n\ge n_0$, so $A(n_0),\dots,A(n)$ are all true. By (sIS), $A(n+1)$ is true. Together, $A(k)$ holds for all $n_0\le k\le n+1$, which is $B(n+1)$.

So $B(n)$ holds for all $n\ge n_0$. Because $B(n)$ contains in particular $A(n)$ (take $k=n$), $A(n)$ holds for all $n\ge n_0$. $\blacksquare$

---

## Aufgabe 2 (Index shift and reversing the order of summation)

Write $m=l+n$ with $n\in\mathbb N_0$.

### a) $\displaystyle\sum_{j=l}^{m} a_j=\sum_{j=l+k}^{m+k} a_{j-k}$ for all $k\in\mathbb Z$

Fix $l,k\in\mathbb Z$. We prove the statement by induction on $n$, for all $a_l,\dots,a_{l+n}\in\mathbb R$.

*Base case $n=0$.* The left side is $a_l$. The right side is $\sum_{j=l+k}^{l+k}a_{j-k}=a_{(l+k)-k}=a_l$.

*Induction step $n\to n+1$.* By the recursive definition and the induction hypothesis (IH):

$$
\sum_{j=l}^{l+n+1} a_j=\sum_{j=l}^{l+n} a_j+a_{l+n+1}
\overset{\text{IH}}{=}\sum_{j=l+k}^{l+n+k} a_{j-k}+a_{(l+n+1+k)-k}
=\sum_{j=l+k}^{l+n+1+k} a_{j-k}.
$$

In the last step we used the recursive definition again: the term for $j=l+n+1+k$ is $a_{l+n+1}$. $\blacksquare$

### b) $\displaystyle\sum_{j=l}^{m} a_j=\sum_{j=l}^{m} a_{m+l-j}$

**Lemma (splitting off the first term).** For all $l\in\mathbb Z$, $n\in\mathbb N_0$ and $a_l,\dots,a_{l+n+1}$:

$$
\sum_{j=l}^{l+n+1}a_j=a_l+\sum_{j=l+1}^{l+n+1}a_j.
$$

*Proof by induction on $n$.* For $n=0$, both sides equal $a_l+a_{l+1}$. For the step $n\to n+1$:

$$
\sum_{j=l}^{l+n+2}a_j=\sum_{j=l}^{l+n+1}a_j+a_{l+n+2}\overset{\text{IH}}{=}a_l+\sum_{j=l+1}^{l+n+1}a_j+a_{l+n+2}=a_l+\sum_{j=l+1}^{l+n+2}a_j,
$$

using associativity of addition. $\square$

**Proof of b).** By induction on $n$ we prove the statement

$$
P(n):\ \text{for all } l\in\mathbb Z \text{ and all } a_l,\dots,a_{l+n}\in\mathbb R:\quad \sum_{j=l}^{l+n}a_j=\sum_{j=l}^{l+n}a_{2l+n-j}.
$$

The quantifier "for all $l$" must be part of $P(n)$, because the step applies the IH with a different lower index.

*Base case $n=0$.* The right side is $a_{2l-l}=a_l$, which equals the left side.

*Induction step $n\to n+1$.* Let $l\in\mathbb Z$ and $a_l,\dots,a_{l+n+1}\in\mathbb R$. We apply the IH to the family $a_{l+1},\dots,a_{(l+1)+n}$, which has lower index $l+1$:

$$
\sum_{j=l+1}^{l+n+1}a_j=\sum_{j=l+1}^{l+n+1}a_{2(l+1)+n-j}=\sum_{j=l+1}^{l+n+1}a_{2l+n+2-j}.
$$

Next we use part a) with $k=-1$ on the family $c_j:=a_{2l+n+2-j}$ for $j=l+1,\dots,l+n+1$. This gives $\sum_{j=l+1}^{l+n+1}c_j=\sum_{j=l}^{l+n}c_{j+1}$, and therefore

$$
\sum_{j=l+1}^{l+n+1}a_j=\sum_{j=l}^{l+n}a_{2l+n+1-j}.
$$

Combining the Lemma, the last identity and the recursive definition:

$$
\sum_{j=l}^{l+n+1}a_j\overset{\text{Lemma}}{=}a_l+\sum_{j=l}^{l+n}a_{2l+n+1-j}
=\sum_{j=l}^{l+n}a_{2l+n+1-j}+a_{2l+n+1-(l+n+1)}
=\sum_{j=l}^{l+n+1}a_{2l+(n+1)-j}.
$$

The middle step uses commutativity and $a_{2l+n+1-(l+n+1)}=a_l$. The result is $P(n+1)$, because $m+l=2l+(n+1)$. $\blacksquare$

---

## Aufgabe 3 (Induction and telescoping sums)

### a) $\displaystyle\sum_{k=0}^n(k+2)2^k=(n+1)2^{n+1}$ for all $n\in\mathbb N_0$

*Base case $n=0$.* The left side is $(0+2)\cdot 2^0=2$ and the right side is $1\cdot 2^1=2$.

*Induction step $n\to n+1$.*

$$
\sum_{k=0}^{n+1}(k+2)2^k\overset{\text{IH}}{=}(n+1)2^{n+1}+(n+3)2^{n+1}=(2n+4)2^{n+1}=(n+2)2^{n+2}. \qquad\blacksquare
$$

### b) $\displaystyle\sum_{k=0}^n(a_k-a_{k+1})=a_0-a_{n+1}$

The proof is by induction on $n\in\mathbb N_0$, for all $a_0,\dots,a_{n+1}$.

*Base case $n=0$.* The left side is $a_0-a_1$.

*Induction step.*

$$
\sum_{k=0}^{n+1}(a_k-a_{k+1})\overset{\text{IH}}{=}(a_0-a_{n+1})+(a_{n+1}-a_{n+2})=a_0-a_{n+2}.\qquad\blacksquare
$$

*Product version* (for $a_1,\dots,a_{n+1}\neq 0$). The same induction works:

- For $n=0$ the product is $\frac{a_0}{a_1}$.
- For the step: $\frac{a_0}{a_{n+1}}\cdot\frac{a_{n+1}}{a_{n+2}}=\frac{a_0}{a_{n+2}}$.

### c) Proof of a) using the telescoping sum

We look for $a_k$ with $a_k-a_{k+1}=(k+2)2^k$. Set $a_k:=-k\,2^k$. Then

$$
a_k-a_{k+1}=-k2^k+(k+1)2^{k+1}=2^k\big(-k+2k+2\big)=(k+2)2^k .
$$

By b):

$$
\sum_{k=0}^n(k+2)2^k=a_0-a_{n+1}=0+(n+1)2^{n+1}. \qquad\blacksquare
$$

(This still relies on b), which was proved by induction. The point is that a) itself needs no separate induction.)

---

## Aufgabe 4 [5 Punkte] $\displaystyle\binom{2n}{n}\ge\frac{4^n}{2n}$ for all $n\in\mathbb N$

**Preliminary identity.** For $n\in\mathbb N_0$:

$$
\binom{2n+2}{n+1}=\frac{(2n+2)!}{(n+1)!\,(n+1)!}=\frac{(2n+2)(2n+1)\,(2n)!}{(n+1)^2\,n!\,n!}=\frac{2(2n+1)}{n+1}\binom{2n}{n}.
$$

*Base case $n=1$.* We have $\binom21=2$ and $\frac{4^1}{2}=2$, so $2\ge 2$ holds.

*Induction step $n\to n+1$.* Let $n\in\mathbb N$ with $\binom{2n}{n}\ge\frac{4^n}{2n}$. The factor $\frac{2(2n+1)}{n+1}$ is positive, so multiplying the IH by it preserves the inequality:

$$
\binom{2n+2}{n+1}=\frac{2(2n+1)}{n+1}\binom{2n}{n}\ \overset{\text{IH}}{\ge}\ \frac{2(2n+1)}{n+1}\cdot\frac{4^n}{2n}=\frac{(2n+1)\,4^n}{n(n+1)}.
$$

Since $2n+1>2n$ and $\frac{4^n}{n(n+1)}>0$:

$$
\frac{(2n+1)\,4^n}{n(n+1)}\ \ge\ \frac{2n\cdot 4^n}{n(n+1)}=\frac{2\cdot 4^n}{n+1}=\frac{4^{n+1}}{2(n+1)}.
$$

Hence $\binom{2(n+1)}{n+1}\ge\frac{4^{n+1}}{2(n+1)}$. $\blacksquare$

---

## Aufgabe 5 [4 Punkte] Multinomial coefficients are natural numbers

**Used fact (lecture, Pascal's rule).** For $n\in\mathbb N_0$ and $0\le m\le n$, $\binom nm=\frac{n!}{m!(n-m)!}\in\mathbb N$.

(If you want a proof: induction on $n$ via $\binom{n+1}{m}=\binom{n}{m-1}+\binom nm$ for $1\le m\le n$, with $\binom{n+1}{0}=\binom{n+1}{n+1}=1$.)

**Claim.** We prove by induction on $r\in\mathbb N$:

$$
P(r):\ \text{for all } n\in\mathbb N_0 \text{ and all }(k_1,\dots,k_r)\in\mathbb N_0^{r}\text{ with } \sum_{i=1}^r k_i=n:\quad \frac{n!}{k_1!\cdots k_r!}\in\mathbb N .
$$

*Base case $r=1$.* Then $k_1=n$ and $\frac{n!}{n!}=1\in\mathbb N$.

*Induction step $r\to r+1$.* Let $n\in\mathbb N_0$ and $(k_1,\dots,k_{r+1})\in\mathbb N_0^{r+1}$ with $\sum_{i=1}^{r+1}k_i=n$. Set $m:=\sum_{i=1}^r k_i$. All $k_i\ge 0$, so $0\le m\le n$ and $k_{r+1}=n-m$. Then

$$
\frac{n!}{k_1!\cdots k_r!\,k_{r+1}!}=\underbrace{\frac{n!}{m!\,(n-m)!}}_{=\binom nm\in\mathbb N}\cdot\underbrace{\frac{m!}{k_1!\cdots k_r!}}_{\in\mathbb N\text{ by IH}} .
$$

The IH applies here because $(k_1,\dots,k_r)\in\mathbb N_0^r$ with $\sum_{i=1}^r k_i=m\in\mathbb N_0$. A product of two natural numbers is a natural number, so the multinomial coefficient lies in $\mathbb N$. This is $P(r+1)$. $\blacksquare$

---

## Aufgabe 6 (Well-ordering)

### a) [4 P] If $A\subseteq\mathbb N$ has no smallest element, then $n\notin A$ for all $n\in\mathbb N$

We use strong induction (Aufgabe 1) with $n_0=1$ and $A(n): n\notin A$.

*(sIA) $1\notin A$.* Suppose $1\in A$. Every $y\in A\subseteq\mathbb N$ satisfies $y\ge1$. Then $1$ would be a smallest element of $A$, a contradiction.

*(sIS).* Let $n\ge1$ and assume $1,\dots,n\notin A$. Suppose $n+1\in A$. Take any $y\in A$. Then $y\in\mathbb N$ and $y\notin\{1,\dots,n\}$. Every natural number is either $\le n$ (and then lies in $\{1,\dots,n\}$) or $\ge n+1$, since there is no integer strictly between $n$ and $n+1$. So $y\ge n+1$. This makes $n+1\in A$ a smallest element of $A$, a contradiction. Therefore $n+1\notin A$.

By strong induction, $n\notin A$ for all $n\in\mathbb N$. In other words, $A=\emptyset$. $\blacksquare$

### b) [1 P] Every nonempty $A\subseteq\mathbb N$ has a smallest element

Let $\emptyset\ne A\subseteq\mathbb N$. Suppose $A$ had no smallest element. By a), $n\notin A$ for every $n\in\mathbb N$. Since $A\subseteq\mathbb N$, this gives $A=\emptyset$, a contradiction. $\blacksquare$

### c) [1 P] The statement is false: $\mathbb Z$ is not well-ordered

**Counterexample:** $B=\mathbb Z$ (or $B=\{-n:n\in\mathbb N\}$). $B$ is nonempty. Suppose $x\in B$ were a smallest element. Then $x-1\in B$ and $x-1<x$, so $x\le x-1$ fails, a contradiction. Hence $B$ has no smallest element. $\blacksquare$

---

## Aufgabe 7 (Fixed points of involutions)

Throughout, $f:A\to A$ satisfies $f\circ f=\mathrm{id}_A$.

**Key lemma.** Let $a\in A$ with $b:=f(a)\neq a$. Then:

1. $f(b)=a$;
2. $A':=A\setminus\{a,b\}$ satisfies $f(A')\subseteq A'$;
3. the restriction $g:A'\to A'$, $g(x):=f(x)$, satisfies $g\circ g=\mathrm{id}_{A'}$;
4. $\sharp A'=\sharp A-2$.

*Proof.*

1. $f(b)=f(f(a))=a$.
2. Let $x\in A'$. If $f(x)=a$, then $x=f(f(x))=f(a)=b$, contradicting $x\notin\{a,b\}$. If $f(x)=b$, then $x=f(b)=a$, again a contradiction. So $f(x)\in A'$.
3. For $x\in A'$: $g(g(x))=f(f(x))=x$.
4. $a\ne b$ and both lie in $A$, so we remove exactly two elements. $\square$

Note also that $x\in A'$ is a fixed point of $g$ if and only if it is a fixed point of $f$.

### a) [5 P] If $n$ is odd, $f$ has a fixed point

$n$ is odd if and only if $n=2k-1$ for some $k\in\mathbb N$. By induction on $k$ we prove:

$$
P(k):\ \text{for every finite set } A \text{ with } \sharp A=2k-1 \text{ and every } f:A\to A \text{ with } f\circ f=\mathrm{id}_A,\ f \text{ has a fixed point}.
$$

*Base case $k=1$.* $\sharp A=1$, so $A=\{a\}$. The only possible value of $f(a)$ is $a$, so $a$ is a fixed point.

*Induction step $k\to k+1$.* Let $\sharp A=2k+1$ and let $f$ be an involution on $A$. Pick some $a\in A$; this is possible because $A\ne\emptyset$.

- If $f(a)=a$, then $a$ is a fixed point and we are done.
- Otherwise $b:=f(a)\ne a$. By the key lemma, $g=f|_{A'}:A'\to A'$ is an involution on $A'=A\setminus\{a,b\}$ with $\sharp A'=2k+1-2=2k-1\ge1$. By the IH, $g$ has a fixed point $x\in A'$. Then $f(x)=g(x)=x$, so $x$ is a fixed point of $f$.

Hence $P(k+1)$ holds. $\blacksquare$

(The sheet's hint that $f$ is bijective, from Blatt 2 Aufgabe 7 b), is not needed in this argument. The restriction works by part 2 of the lemma.)

### b) [2 P] $n-\sharp F$ is even

Note that $F\subseteq A$, so $0\le\sharp F\le n$.

We use strong induction on $n=\sharp A\in\mathbb N$ (Aufgabe 1, $n_0=1$) and prove the statement for all finite sets $A$ with $\sharp A=n$ and all involutions $f$ on $A$.

*(sIA) $n=1$.* $A=\{a\}$ and $f(a)=a$, so $F=A$ and $n-\sharp F=0$, which is even.

*(sIS).* Let $n\ge1$ and assume the claim for all sizes $1,\dots,n$. Let $\sharp A=n+1$ and let $f$ be an involution on $A$.

- If $F=A$, then $n+1-\sharp F=0$, which is even.
- Otherwise pick $a\in A\setminus F$ and set $b:=f(a)\ne a$. Since $f(b)=a\neq b$, also $b\notin F$. Hence $F\subseteq A'=A\setminus\{a,b\}$. The fixed points of $g=f|_{A'}$ are exactly $F_g=F\cap A'=F$. Also $\sharp A'=n-1$.
  - If $n-1=0$: then $A=\{a,b\}$ and $F=\emptyset$, so $n+1-\sharp F=2$, which is even.
  - If $1\le n-1\le n$: the IH applied to $(A',g)$ says $(n-1)-\sharp F$ is even. Then $(n+1)-\sharp F=\big((n-1)-\sharp F\big)+2$ is also even.

$\blacksquare$

*Remark.* b) implies a) directly. If $n$ were odd and $F=\emptyset$, then $n-\sharp F=n$ would be even, a contradiction.
