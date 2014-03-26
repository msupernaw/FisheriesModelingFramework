Generic Template library for NOAA NMFS fisheries stock assessment modeling.

Description:

Template based classes and routines provide reusable code. Template classes 
take two template arguments, BASE_TYPE and EVAL_TYPE. The default for 
EVAL_TYPE is a BASE_TYPE. This allows for flexible modeling when a non-primitive
type is used for evaluations. Examples of non-primitive types are automatic differentiable 
types, such as ADNumbers or dvariables.


For instance:
<pre><code>

//evaluation types will be dvariables
AgeBasedPopulation&lt;double, dvariable&gt; population; 

//evaluation types will be ADNumbers with a basetype of float
AgeBasedPopulation&lt;float, ad::ADNumber&lt;float&gt; &gt; population; 

//evaluation types will be BigFloat
AgeBasedPopulation&lt;double, ad::BigFloat&lt;double&gt; &gt; population; 

</code></pre>


This code makes heavy use of polymorphism/inheritance to provide flexibility. 

Fish populations are represented in the code by data modules derived from the base class PopulationDM,
which hold relevant information about the fish popolation. Special functors are developed that make evaluations
based on input in the form of a PopulationDM. Functors can be operations that evaluate mortality, recruitment,
selectivity, etc. This design provides flexibilty to accomidate many types of modeling efforts within NMFS.