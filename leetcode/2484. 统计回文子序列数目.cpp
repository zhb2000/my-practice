// region header
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <format>

using namespace std;

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << '[';
    bool first = true;
    for (const T &x : v)
    {
        if (first)
            first = false;
        else
            os << ", ";
        os << x;
    }
    os << ']';
    return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &matrix)
{
    os << '[';
    bool first_row = true;
    for (const std::vector<T> &row : matrix)
    {
        if (first_row)
            first_row = false;
        else
            os << ",\n ";
        os << '[';
        bool first_col = true;
        for (const T &val : row)
        {
            if (first_col)
                first_col = false;
            else
                os << ", ";
            os << val;
        }
        os << ']';
    }
    os << ']';
    return os;
}
// endregion

#include <bit>
#include <ranges>
#include <span>
namespace rng = std::ranges;
namespace vs = std::views;
using ll = long long;
using ull = unsigned long long;

class Solution
{
public:
    static constexpr int MOD = int(1e9 + 7);

    int countPalindromes(const string &s)
    {
        int n = int(s.length());
        auto prefix = vector(n, vector<int>(10));              // prefix[n][10]
        auto prefix2 = vector(n, vector(10, vector<int>(10))); // prefix2[n][10][10]
        auto suffix = prefix;
        auto suffix2 = prefix2;
        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c < 10; c++)
            {
                prefix[i][c] = (i - 1 >= 0) ? prefix[i - 1][c] : 0;
                if (s[i] - '0' == c)
                    prefix[i][c] += 1;
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int c = 0; c < 10; c++)
            {
                suffix[i][c] = (i + 1 < n) ? suffix[i + 1][c] : 0;
                if (s[i] - '0' == c)
                    suffix[i][c] += 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int c1 = 0; c1 < 10; c1++)
            {
                for (int c2 = 0; c2 < 10; c2++)
                {
                    prefix2[i][c1][c2] = (i - 1 >= 0) ? prefix2[i - 1][c1][c2] : 0;
                    if (s[i] - '0' == c2)
                        prefix2[i][c1][c2] += (i - 1 >= 0) ? prefix[i - 1][c1] : 0;
                }
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int c2 = 0; c2 < 10; c2++)
            {
                for (int c1 = 0; c1 < 10; c1++)
                {
                    suffix2[i][c2][c1] = (i + 1 < n) ? suffix2[i + 1][c2][c1] : 0;
                    if (s[i] - '0' == c2)
                        suffix2[i][c2][c1] += (i + 1 < n) ? suffix[i + 1][c1] : 0;
                }
            }
        }
        int ans = 0;
        for (int i = 2; i + 2 < n; i++)
        {
            for (int c1 = 0; c1 < 10; c1++)
            {
                for (int c2 = 0; c2 < 10; c2++)
                {
                    ll temp = ll(prefix2[i - 1][c1][c2]) % MOD * ll(suffix2[i + 1][c2][c1]) % MOD;
                    ans = (ans + int(temp)) % MOD;
                }
            }
        }
        return ans;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->countPalindromes("103301") == 2);
    assert(sol()->countPalindromes("0000000") == 21);
    assert(sol()->countPalindromes("9999900000") == 2);

    string s = "9933074172680895382920409963798815514779967443792629619088352447493663482705102716083690152958175523385598038579381199522067164478522726997789130759557496806139744347042243941894706696975672151178376798687517403570200507168982358631153576468351714931365085924589918578760923175811136393320328358322385187510379706365487492862847366345969354708041529144805426102657078232857991240163186878099507097982024112681510409542310843980336690298269744334124916649623117771769446721572184070780332579441767280752048617103385873744666438193171681345125911131707297775497283637984153914775333295555996218447153693141499694440800400509357708482386539248711991591867413678890206337657936087691464690158948799793288674641899805532205271616355174854575524911101337957783667314195944145306470475308247979115605127051593447487491744951280342273498355731357580699969312617459352023141736146015118104078333849830221587908161714572647957711697561502876295775162786012813226484711840353137171253974716673002293952771965239713254135092476873699344223322086270433176838489186242671039126335931503887712575831271114019298607051682875806281704973107692636769763489278213183674493427083977283507737015908691608066226083514226718822086180046937383377956004393818433393334174587865109984490472749538147293247132397745187567827982014503421746385225541486180841384534387060969152780636254846080580048195090563904218929688305432390309815318802642224119911418880395320061637689619017950865348816214721387693761616699270142016196629097980924799822105059914081519743635598707653209802386770263520151342833694609341787856047674379900759877105792126288523392376411166765003430014424126493950267581234194425658802653802917485593208335212568257420790981301353498838202552278129984322995228752825818748319812276053949175895145067909663210627259944808342124513954800658872360902658340112856604097896664021351297080624023487044925199549077859198912435417678300856350714010111551311568510921599489647088272737287326273070359451484706310798411610035203020325819229575071673865185634111616176988163824649392159152191086612877725798919461794221181036098694837548441283846480128643163674708547682231576428295245473119495178372577358004923715512415041540947599214267686694962995032572558244277087690470916227460288559392186684090587398583723182436894673727731730555861868207532130362555740928646277258416687017446618839314950147795660814650572344205245330551733519612243134087448683638428027100584214283299065005883210909121492103689276019812035856474581430174198015694212807797733222529648520464903848409384989754455853533723989162866740146682920110754255951357195842122013960418723828168831789960199274324037155012092800992033345769430682499719115693388648142455050935250219399240746795246782447532227447065874260623559595500911141470838053741002125583159638375035083298193213898506526254569203984621671449961960552460625231429221675625388402372893863507224474477761768055278728492744624307666732351053780371049810456131276494308206382033937270513183237147975963244658807701252866811921123298904543515638043913469855404612725205147429158570673407067663842060732022796576378063877516976554059591381899622470331040671138757368769629410777436144675477243361500864489028855210007413408817813148801351943217469903986923401919600360645008827762510709015538966116393200360099863353495795525452233975892929818910017284304925583608737992721730486091854188140570859947608451085634801336091926455878619304508574540626821620315797039336338879096776360167495754144988700149395797178876278230412761357201545197201236408473967174796866904379292253186725209254355512521619106917164296072558225511526700393258076927601199320408747279558496025849267034514866961325972464871578561450354235821653518384610742300253687436437850832157680235290313369656259498052909404344691455027969903117600352261846639149540694436379831575208244078171739805105349953106355457420908014045363351830338962536208009521810528830089053346927794438098958503136821504280126388666686231033301249628165331803386490504927026941182504026743978880651772684596738784091033248344124769759220238581995035453122033171332968613022621110317524757957924522638651503986318704644873997609609206761945687703735671616015786463113349827949411568690786452535619830505168577955567866634704953431599188533230977641143003992962740051977965777823908498916575724137829895390916633624636137465584749808573829389066009280845623182058422660027870444085113538113659749432641776407188908328631445836200252019554079205691290305185804163278648170655019130997805109943057980494517302823599620340212565727136757931047206504921411489214969141567959558467813423389042771490892532904141047705118730807271906176973988465347309316837974913983445299420302771147568660069567259924888060291428257814523151164491783529632386613888336051376296719182089950449759978016476203325262964637159874907599688056412615862207211472539779087033757605979642721741664527106163948021905712922608853316199252362392957352928368484218569402935642924934312726334667098203043234924825423781843574113641375440271649150310747397657588910640873004017861567520886374441544054882414813097461552754623426381752236524232663509958090599147065862017213038010223956861590350359998043542704775622341252813203739031097274242812569431835958048969801774750801703300065992742604862424216875371881510672527900697094286196735972593582566779357144250740956598123298476060226440796987974129562992699345923838893431866695332468363887784710197714155593524777076336542918547296457487520914121537762584508834824225264437779789805583146584779160610207011798842832290593118875122576943467302733261113149855494210729515729043561393926782359213545877717162768251263300142666138466745820254063583798558403465823542480769551003339601637626825339380520494583774949560451100713269910875199815870067928373992691590886475624142235003384597567795569040388447518947683935973139651097585444121794724450661845479784382899634595931984684849622838044769930946490463128124553332722995421437049032664131668591471127225756272599320785896565712145395487196379960696182291455087613201526685133539613459481635370707780958096487888649509304411612350350755132186621553437688285542867149582652418244876580486234694982161047298868725103050846159516898885838958825341667856655863954019410798703481511150474061080405756842050117651524834925842321749731876370225520929891244433888863986720184396128886152385864899653381129599335382918419604144355053486156962621221570320004725132325127481446233360668237303219667940339820140320604826340285286002290668825682607204306678872775979745032137136230451669376596172540862989795904000664204117638023601980126171539112019943144310676119602417638035854331370291962685599646561003194102297404768144580340514755306624975735561765933945392445417836250834476907988959179757355116520023257280220182000643798274348163550331680635368132153708055083460272415301893564495677984649155078367695447477502171091577530528302009875833418460882383170391648797866506511930156393315708566678935134176773225375771688272469738352649541740233312920301789660171963000425110817996429655544957147233910409096350554412544923423354996256499132192991679699810602675608115305425693416285356580548426351617269932619533335302077299556819707793637599765313950866595119314954039680874668370545992967674755231512904545383817476479175745754347758534348434549163520078624392389050576495836802463516401402430804418129285924343203464394990441267642083072480301129954612652866208501724157916733048027046791940676804268685637854929282409611546982114023648177560514634649130535217530014660237436085385039768395594285384991663253531862278482317956229889179327445491931553676409355475209499729657010613295231972014232905571789318506045694867747439874710210785023857734803541015440789308173997922448358309452075346546138973215508484168818482775752089783052809528109907413980436316889733864675359364536092102976162974228505330702783397136322330061573970672244961309179262099131309283833659978895887810480428764950944292558911782401031453040420351246431693415323197529928602194555172776324063312928583738807683081759159960503594152292894631301344105770980635982920357070392273467468032624158268400638466738904124193373163359428650281714999315507202027832198125995093153346023712704434233891795505628960984254295109113181786692128148749301363718863144405864174491267092913510105085234981966527401169381171727919044347632883996593876351908275482998897941809991928067693914806426234756992874500689051143070886395971427077347666326848685292206717164477877428037885478344989147924998998233153811190289335790733604880953985930053565611271928210563954258724803386396498332647911154595237994335746368698970291141040639070533788658432302700537193007904750219276441617438419162350134672288532396017209741242732996788367069223029548038035520329745250372711202667959203421615721760320599077797110780682392022840541371876805364762205525557138611892023806178190292069607863229311204044036390194923577764746626734489647873563514438273724908598266478190843187446613168789374393464223994613679475732370934475873384380971906968803367461630683784629600763857684139651248967563190327927326547116611406460446961880115126710897822329918677673092979195825042535007528567591960294553677943383942678925376664313946059896013929310677003833854517566167382990615419294580629233331610226657219767979923967586766588345665217653654508896056628076069003776751246847910427014132518454856723082442725373408180650679296323755008339992112913396808769960385644011269425403996975381969232004103335624821957333355691911967825333027768849981069770412095123362112924216463764169158066903699422053675668593013172234210874831736490251236642310199125772980671816015395046308443435628342930079843933872393878327247191899078036722890618785725546572668537185155258091934626381071483931307404555242315662764012652837655358818964517361720854079389609255882375714862314574180661211574271857993564043568155415410200024350287947903007900920187226552879441938012";
    cout << "s.len: " << s.length() << endl;
    cout << sol()->countPalindromes(s) << endl;

    return 0;
}
