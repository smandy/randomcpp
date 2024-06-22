import os, re

vanillaEnv = Environment(
    CPPFLAGS  = ['-std=c++23', '-g']
)

vanillaEnv.Tool('compilation_db')
vanillaEnv.CompilationDatabase()

def makeObject(x):
    return vanillaEnv.Object(source = f'{x}.cpp', target = f'build/{x}.o')

extraDeps = {}

def makeProgram(prog, **kwargs):
    o = vanillaEnv.Object( source = f'{prog}.cpp' ,target=f'build/{prog}')
    kwargs = extraDeps.get(prog, kwargs)
    #print(f"kwargs for {prog} are {kwargs}")
    vanillaEnv.Program(source = o, target = f'bin/{prog}', **kwargs)

mmapper, pingPong, mpmc, rateTimer, trade, tradeServer, vwap  = [ makeObject(x) for x in 'mmapper,pingPong,mpmc,rateTimer,trade,tradeServer,vwap'.split(',') ]

for k,v in { 'twonk,fileSystem,filesystemExperiment' :  { 'LIBS' : ['boost_system', 'boost_filesystem'] },
             'testRateTimer,ping,pong' : { 'LIBS': [pingPong, mmapper, rateTimer]},
             'jsonExample' : { 'LIBS' : ['jsoncpp', 'docopt'] },
             'active_object,queue_test' :  { 'CPPFLAGS' :['-DTBB_USE_DEBUG=1'],
                                             'LIBS' : ['tbb', 'pthread'] },
             'testMpmc,mpmcSanity' : { 'LIBS' : [mpmc]},
             'xcbexample' : { 'LIBS' : ['xcb'] },
             'tradeReader,tradeServerMain,tradeClientMain,tradeSourceImpl,vwapNetworkClient' : { 'LIBS' : [mmapper, trade, tradeServer] }
            }.items():
    bits = k.split(',')
    for bit in bits:
        #print(f"bit={bit} v={v}")
        extraDeps[bit] = v

progs = re.split("[ \\n]", """move relations moveTest2 traits
forwarding forwarding2 doit lockExperiment tmp lfq rdtsc
intraProcessPingPong myers crtp crtp2 tupple exper funcStuff async
transform transform3 condition tupleFun pointerFun socketServer pmf
ecpp2 ecpp4 rose selectif abbrev constVec erasure logExperiment
backInserterEquiv socketServer2 transform2 echoServer parameterPack
threadTest myers2 memfunStuff vectorCast property_tree lambdaTemplate
tcpclient tupleInit knightTour knightTour2 helloWorld stringTest
testPrettyPrint myPromise cherryPick packFun moveCapture initList
chatServer bindFun stringReverse arrayDecay scopeExperiment lineReader
boostRefCountExample destructor printTest virtualExperiment2 dynclass
except stringReverse2 synctimer timer periodic functors daytimeClient
daytimeServer asyncDatetimeServer streambuf_example read_until_example
baseTest read_a_file vector_test complex_test destructure copy_test
vectorfun transform_test overload testb maptest mutabletest google jen
foo moveTest3 bindExample overloaded sink boost_shared_memory
optimizer foldExpression owner variadic sfinae sfinae2 stdalign
noexcept nomove elision exceptions marketDataExample shared_lock
finalizer hammer arrayTest polygon stairs helloWorld
exprtk_sqrt_newton_raphson sharedFromThisTest""")

for prog in progs:
    makeProgram(prog)



