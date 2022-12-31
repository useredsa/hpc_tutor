## Function Signatures

Different implementations of the same algorithm,
for example, sequential and parallel,
have the same function name prefix,
which is the name of the most basic implementation
(sequential and possibly non-caché friendly).
In the non-basic implementations,
this suffix is followed by a string of the form `_[b][t][[(s|a|c)m][g]`,
where each character that appears shows a particular thing:

* `b`: Uses block (tiling) decomposition.
* `t`: Uses thread-level parallelism.
* `m`: Uses process-level parallelism via message passing.
* `sm`: Uses syncrhonous process-level parallelism via message passing.
* `am`: Uses asyncrhonous process-level parallelism via message passing.
* `cm`: Uses collective process-level parallelism via message passing.
* `g`: Uses the GPU.
