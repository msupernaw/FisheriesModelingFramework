Generic Template library for NOAA NMFS fisheries stock assessment modeling.

Description:

Template based classes and routines provide reusable code. Template classes 
take two template arguments, BASE_TYPE and EVAL_TYPE. The default for 
EVAL_TYPE is a BASE_TYPE. This allows for flexible modeling when a non-primitive
type is used for evaluations. Examples of non-primitive types are automatic differentiable 
types, such as ADNumbers or dvariables.


For instance:
<pre><code>


//evaluation types will be double
AgeBasedPopulation&lt;double&gt; population;

//evaluation types will be dvariables
AgeBasedPopulation&lt;double, dvariable&gt; population; 

//evaluation types will be ADNumbers with a basetype of float
AgeBasedPopulation&lt;float, ad::ADNumber&lt;float&gt; &gt; population; 

//evaluation types will be BigFloat
AgeBasedPopulation&lt;double, ad::BigFloat&lt;double&gt; &gt; population; 

</code></pre>


This code makes heavy use of polymorphism/inheritance to provide flexibility. 

Fish populations are represented in the code by data modules derived from the base class PopulationDM,
which hold relevant information about the fish population. Special functors are developed that make evaluations
based on input in the form of a PopulationDM. Functors can be operations that evaluate mortality, recruitment,
selectivity, etc. This design provides flexibility to accommodate many types of modeling efforts within NMFS.

For example:


<pre><code>
  //create a population data module
    noaa::nmfs::AgeBasedPopulation&lt;double&gt; population;

    //create a functor list
    std::vector&lt;noaa::nmfs::PopulationFunctor&lt;double&gt;* &gt;functors;

    //make a recruitment functor and add it to the list
    noaa::nmfs::recruitment::agebased::BevertonHolt&lt;double&gt; beverton_holt;
    functors.push_back(&beverton_holt);

    //make a selectivity functor and add it to the list
    noaa::nmfs::selectivity::agebased::Logistic&lt;double&gt; logistic_selectivity;
    functors.push_back(&logistic_selectivity);

    //make a mortality functor and add it to the list
    noaa::nmfs::mortality::agebased::ConstantRateMortality&lt;double&gt; constant_rate_mortality;
    functors.push_back(&constant_rate_mortality);

    double ret = 0;

    //all functors provide the routine
    // const EVAL_TPYE Evaluate(noaa::nmfs::PopulationDM&lt;BASE_TYPE,EVAL_TYPE&gt;* population) 
    for (int i = 0; i &lt; functors.size(); i++) {
        ret += functors[i]->Evaluate(&population);
    }
</code></pre>

To-do:<br/>
<br/>
1) Make dvariable wrapper class(or just define cmath functions in namespace std).<br/>
2) Define functors already present in stock synthesis<br/>
3) Finish polygon/geo area class<br/>
4) Write routine for nearest neighbor list building for populations<br/>
5) Write SizeBasedPopulation class <br/>
6) Define size based functors.<br/>
7) Create unit tests<br/>
8) Come up with a catchier name!<br/>




