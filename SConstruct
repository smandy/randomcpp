import os, re

vanillaEnv = Environment(CPPFLAGS  = ['-std=c++23', '-g'])

vanillaEnv.Tool('compilation_db')
vanillaEnv.CompilationDatabase()

def makeObject(x):
    return vanillaEnv.Object(source = f'{x}.cpp', target = f'build/{x}.o')

mmapper, pingPong, mpmc, rateTimer, trade, tradeServer, vwap = \
    [ makeObject(x) for x in 'mmapper,pingPong,mpmc,rateTimer,trade,tradeServer,vwap'.split(',') ]

def makePrograms(env):
    progNames = re.split("[ \\n]+", """move relations moveTest2 traits
    forwarding forwarding2 doit lockExperiment tmp lfq rdtsc
    intraProcessPingPong myers crtp crtp2 tupple exper funcStuff async
    transform transform3 condition tupleFun pointerFun socketServer
    pmf ecpp2 ecpp4 rose selectif abbrev constVec erasure
    logExperiment backInserterEquiv socketServer2 transform2
    echoServer parameterPack threadTest myers2 memfunStuff vectorCast
    property_tree lambdaTemplate tcpclient tupleInit knightTour ctad
    knightTour2 helloWorld stringTest testPrettyPrint myPromise
    cherryPick packFun moveCapture initList chatServer bindFun
    stringReverse arrayDecay scopeExperiment lineReader
    boostRefCountExample destructor printTest virtualExperiment2
    dynclass except stringReverse2 synctimer timer periodic functors
    daytimeClient daytimeServer asyncDatetimeServer streambuf_example
    read_until_example baseTest read_a_file vector_test complex_test
    destructure copy_test vectorfun transform_test overload testb
    maptest mutabletest google jen foo moveTest3 bindExample
    overloaded sink boost_shared_memory optimizer foldExpression owner
    variadic sfinae sfinae2 stdalign noexcept nomove elision
    exceptions marketDataExample shared_lock finalizer hammer
    arrayTest polygon stairs helloWorld exprtk_sqrt_newton_raphson
    sharedFromThisTest twonk fileSystem filesystemExperiment
    testRateTimer ping pong jsonExample active_object queue_test
    testMpmc mpmcSanity xcbexample tradeReader tradeServerMain
    tradeClientMain tradeSourceImpl vwapNetworkClient equal_range""")
    #print(f"Prognames is {progNames}")
    deps = {}
    def add( strProgs, libs, **kwargs):
        bits = strProgs.split()
        value = {}
        value.update(kwargs)
        value['LIBS'] = libs
        for bit in bits:
            #print(f"bit={bit} v={v}")
            if not bit in progNames:
                raise RuntimeError(f"Warning dep for {bit} not in list of progs!")
            deps[bit] = value
            
    add('twonk fileSystem filesystemExperiment' , ['boost_system', 'boost_filesystem'])
    add('testRateTimer ping pong', [pingPong, mmapper, rateTimer] )
    add('jsonExample' , ['jsoncpp', 'docopt'])
    add('active_object queue_test' , ['tbb', 'pthread'], CPPFLAGS = ['-DTBB_USE_DEBUG=1']  )
    add('testMpmc mpmcSanity', [mpmc])
    add('xcbexample' , ['xcb'])
    add('tradeReader tradeServerMain tradeClientMain tradeSourceImpl vwapNetworkClient', [mmapper, trade, tradeServer])
    
    for prog in progNames:
        kwargs = deps.get(prog, {})
        o = env.Object(source = f'{prog}.cpp' ,target=f'build/{prog}')
        env.Program(source = o, target = f'bin/{prog}', **kwargs)

makePrograms(vanillaEnv)
