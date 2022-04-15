#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#define LL long long
#define f first
#define s second
#define V vector
#define all(v) v.begin(), v.end()
using namespace std;

const int mod = 998244353;

V<V<V<bool>>> hide(100, V<V<bool>>(100, V<bool> (100, 0)));

map<char, char> transelect;

V<V<int>> story_list = { //can put some of the value in it
	{
		-1  //null index
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8 // index 0 is null
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 //index 0 is null
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
	},
	{
		0, 1, 2, 3, 4, 5, 6
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7
	},
	{
		0, 1, 2, 3, 4, 5, 6
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7
	},
	{
		0, 1, 2, 3, 4, 5, 6, 7
	},
	{
		0, 1, 2, 3, 4
	}
};

V<V<bool>> story_visited(11, V<bool> (14, 0));

V<V<bool>> story_exist = {
	{
		0 //null index
	},
	{
		0, 1, 0, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 0, 1, 1, 0, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1, 1, 1, 1//index 0 is null
	},
	{
		0, 1, 1, 1, 1//index 0 is null
	}
};

V<V<bool>> story_problem_exist(11, V<bool> (14, 0));


V<V<bool>> story_selection_exist(11, V<bool> (14, 0));

V<pair<int, int>> hide_chap(10, make_pair(0, 0));

int story_chapter_first, story_chapter_second; // chapter.f, chapter.s
void read_story(fstream &file) {
	string text; int row = 0;
	while (getline(file, text)) {
		char ch = '0';
		cout << text << '\n'; row++;
		while (ch != '\n' && (~row & 1)) ch = cin.get();
	}
	//cin.get();
	file.close();
}
string read(pair<int, int> chapter, fstream &file, bool change_seletion_text = false, bool f = 1) {
	string text, text2, ret;
	int cnt = 0, file_cnt = 0; char select;
	while (getline(file, text) && getline(file, text2)) {
		file_cnt++; select = text[1];
		if (hide[chapter.f][chapter.s][file_cnt]) continue;
		if (change_seletion_text == true) text[1] = char('A' + cnt), cnt++;
		transelect[text[1]] = select;
		if (f) cout << ' ' << text << '\n' << text2 << '\n';
		ret += text;
	}
	return ret;
}
void wait_for(int time) { //counted by ms
	int Second_cnt = time / 1000;
	cout << "wait for " << Second_cnt << " seconds";
	while ( Second_cnt ) {
		Second_cnt--;
		cout << '\r';
		Sleep(1000);
		cout << "wait for " << Second_cnt << " seconds           ";
	}
	cout << "\r                                                        \r";
	return;
}


bool exist(size_t chapter_first, size_t chapter_second) { //chapter.f, chapter.s
	return story_exist[chapter_first][chapter_second];
}
void sup_file(pair<int, int> chapter, string str, int i, bool rewrite = false) {
	fstream ifile, ofile;
	if (!rewrite) ifile.open(str + to_string(chapter.f) + "-" + to_string(chapter.s) + ".txt", ios::app);
	else ifile.open(str + to_string(chapter.f) + "-" + to_string(chapter.s) + ".txt", ios::out);
	ofile.open("sup_" + to_string(chapter.f) + "-" + to_string(chapter.s) + "-" + to_string(i) + ".txt", ios::in);
	string text;
	while (getline(ofile, text)) ifile << text << '\n';
	ofile.close();
	ofile.open("sup_" + to_string(chapter.f) + "-" + to_string(chapter.s) + "-" + to_string(i) + ".txt", ios::out);
	ifile.close(), ofile.close();
}
struct story {
	fstream file;
	pair<int, int> chapter, to_story = make_pair(1, 1);
	bool problem_exist, selection_exist, support_exist;

	//static pair<int, int> get_chapter() {return this->chapter;}
	//V<string> story_txt;
	struct support {
		void init(pair<int, int> chapter_copy, bool& support_exist_copy) {
			if (chapter_copy == make_pair(2, 4)) {
				if (story_visited[8][7] && story_visited[6][2])
					sup_file(chapter_copy, "", 1, 1), support_exist_copy = 0;
			}
			if (chapter_copy == make_pair(2, 6)) {
				if (story_visited[1][3])
					sup_file(chapter_copy, "", 1, 1), support_exist_copy = 0;
			}
			if (chapter_copy == make_pair(1, 1)) {
				if (story_visited[2][5] && story_visited[8][6])
					sup_file(chapter_copy, "c_", 1), support_exist_copy = 0;
			}
		}
	} story_support;
	struct problem {
		pair<int, int> to_ch;
		string text, ans;
		bool check(string your_ans) {
			return ans == your_ans || your_ans == "_2147483648";
		}

		pair<int, int> input_ans() {
			//int sec = 20;
			cout << '\n';
			string your_ans;
			cout << "input your answer:";
			getline(cin, your_ans);
			while (!check(your_ans)) {
				if (your_ans != "") {
					cout << "WA\n" ; wait_for(30000); cout << "\ninput your answer:";
					getline(cin, your_ans);
				}
				else cout << "input your answer:", getline(cin, your_ans);
			}
			cout << "AC\n", Sleep(1000);
			return to_ch;
		}

		void init(pair<int, int> chapter_copy) {
			if (chapter_copy == make_pair(4, 1)) to_ch = make_pair(3, 1);
			else if (chapter_copy == make_pair(4, 3)) to_ch = make_pair(3, 3);
			else if (chapter_copy == make_pair(2, 4)) to_ch = make_pair(3, 4);
			else if (chapter_copy == make_pair(2, 6)) to_ch = make_pair(3, 6);
			else if (chapter_copy == make_pair(2, 13)) to_ch = make_pair(1, 3);
			fstream problem_file, ans_file;
			problem_file.open("p_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			ans_file.open("a_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			read(chapter_copy, problem_file, 0);
			if (chapter_copy == make_pair(4, 1)) cout << "--請通知幹部你們正在解越三秋的謎題--\n\n";
			ans = read(chapter_copy, ans_file, 0, 0); /*cout << "ans:" << ans << '\n';*/
		}
		//problem(pair<int, int> _chapter): text(""), ans("") {};
	} story_problem;


	struct selection {
		//V<string> choice;
		map<char, pair<int, int>> to_ch;

		//(A)...
		pair<int, int> check(pair<int, int> chapter_copy) {
			cout << '\n';
			string st;
			do {
				cout << "you can only input ONE CAPITAL letter and the choice should be on the list.\ninput your choice:";
				getline(cin , st);
			} while (st.size() != 1 || !(st[0] >= 65 && st[0] <= 90) || \
			         !transelect.count(st[0]) || !exist(to_ch[transelect[st[0]]].f, to_ch[transelect[st[0]]].s));
			cout << '\n';
			return to_ch[transelect[st[0]]];
		}

		void init(pair<int, int> chapter_copy) {
			if (chapter_copy == make_pair(1, 1)) {
				for (int i = 1; i <= 13; i++) to_ch[char(64 + i)] = make_pair(2, i);
			}
			else if (chapter_copy == make_pair(2, 1)) {
				to_ch['A'] = make_pair(4, 1), to_ch['B'] = make_pair(1, 1);
			}
			else if (chapter_copy == make_pair(2, 3)) {
				to_ch['A'] = make_pair(4, 3), to_ch['B'] = make_pair(1, 1);
			}
			else if (chapter_copy == make_pair(2, 7)) {
				for (int i = 1; i <= 10; i++) to_ch[char(64 + i)] = make_pair(5, i);
			}
			else if (chapter_copy == make_pair(3, 8)) {
				for (int i = 1; i <= 7; i++) to_ch[char(64 + i)] = make_pair(6, i);
			}
			else if (chapter_copy == make_pair(3, 9)) {
				for (int i = 1; i <= 6; i++) to_ch[char(64 + i)] = make_pair(7, i);
			}
			else if (chapter_copy == make_pair(3, 10)) {
				for (int i = 1; i <= 7; i++) to_ch[char(64 + i)] = make_pair(8, i);
			}
			else if (chapter_copy == make_pair(3, 11)) {
				for (int i = 1; i <= 7; i++) to_ch[char(64 + i)] = make_pair(9, i);
			}
			else if (chapter_copy == make_pair(3, 12)) {
				for (int i = 1; i <= 4; i++) to_ch[char(64 + i)] = make_pair(10, i);
			}
			//cout << "selection_init " << chapter_copy.f << ' ' << chapter_copy.s << '\n';
			fstream selection_file, choice_file;
			//selection_file.open("s_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			choice_file.open("c_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			//read(selection_file);
			for (auto & i : hide_chap) {
				if (chapter_copy == i) {
					read(chapter_copy, choice_file, 1); return;
				}
			}
			read(chapter_copy, choice_file);
		}

	} story_selection;
	bool init_txt(pair<int, int> p) {
		file.open(to_string(p.f) + "-" + to_string(p.s) + ".txt", ios::in);
		if (file.is_open()) return true;
		return false;
	}
	pair<int, int> run_story() {
		bool flag = true;
		for (int iter = 8; iter <= 12; iter++) {
			if (chapter == make_pair(2, iter) && story_visited[2][iter]) return make_pair(3, iter);
		}
		if (chapter == make_pair(3, 12)) {
			if (story_visited[10][2] && story_visited[10][3] && story_visited[10][4] && story_visited[5][8])
				return make_pair(1, 4);
		}
		if (story_visited[9][5]) hide[2][7][8] = 0;
		if (story_visited[3][1]) hide[2][7][9] = 0;
		if (story_visited[7][5]) hide[3][11][7] = 0;
		if (story_visited[10][2]) hide[2][7][10] = hide[3][8][7] = hide[3][9][6] = 0;
		if (story_visited[5][8]) hide[3][8][6] = 0;
		if (story_visited[3][3]) hide[3][10][7] = 0;
		if (story_visited[9][4]) hide[3][12][2] = 0;
		if (story_visited[6][7]) hide[3][12][3] = 0;
		if (story_visited[5][6]) hide[3][12][4] = 0;
		if (support_exist) story_support.init(chapter, support_exist);
		if (chapter == make_pair(2, 6) && support_exist == 0) problem_exist = 1;
		else if (chapter == make_pair(2, 4) && support_exist == 0) problem_exist = 1;
		if (story_visited[chapter.f][chapter.s]) {
			if (chapter == make_pair(1, 1)) flag = false;
		}
		if (flag) init_txt(chapter), read_story(file);
		if (problem_exist) {story_problem.init(chapter); return story_problem.input_ans();}

		//story_selection.output();
		if (selection_exist) {story_selection.init(chapter); return story_selection.check(chapter);}
		if (chapter == make_pair(3, 6)) {
			to_story = make_pair(1, 6);
		}
		if (chapter == make_pair(1, 6)) {
			if (story_visited[1][4]) to_story = make_pair(1, 8);
			else to_story = make_pair(1, 7);
		}
		for (int iter = 8; iter <= 12; iter++) {
			if (chapter == make_pair(2, iter)) to_story = make_pair(3, iter);
		}
		if (chapter == make_pair(3, 4)) to_story = make_pair(1, 5);
		if (chapter == make_pair(1, 5) || chapter == make_pair(1, 7) || chapter == make_pair(1, 8))
			to_story = make_pair(10, 10);
		transelect.clear();
		return to_story;
	}
	story(pair<int, int> _chapter, bool _problem_exist, bool _selection_exist, bool _support_exist = false): \
		chapter(_chapter), problem_exist(_problem_exist), selection_exist(_selection_exist), \
		support_exist(_support_exist)
	{
		if (chapter == make_pair(2, 4) || chapter == make_pair(2, 6) || chapter == make_pair(1, 1))
			support_exist = true;
		//init_txt(chapter);
		//see();
		//if (problem_exist) story_problem.init(chapter);

		//story_problem.input_ans();
	}
	story() {};

};

vector<vector<story>> graph;
int stories_init() {
	/*
	    return -1; graph can't initialize
	    return 1; story is finish
	*/
	story_chapter_first = story_chapter_second = 1; //start from s_1-1
	if ( story_list.size() != story_problem_exist.size() ) {
		return -1;
	}
	/*for (size_t i = 0; i < story_list.size(); ++i) {
		if (story_list[i].size() != story_problem_exist[i].size())
			return -1;
	}*/
	//vector<vector<story>> graph;
	for (size_t i = 0; i < story_list.size(); ++i) {
		graph.push_back(V<story>(0));
		for (size_t j = 0; j < story_list[i].size(); ++j) {
			graph[i].push_back(story(make_pair(i, j), story_problem_exist[i][j], story_selection_exist[i][j]));
		}
	}
	hide_chap[0] = make_pair(2, 7);
	for (int i = 1; i <= 5; i++) hide_chap[i] = make_pair(3, i + 7);
	hide[2][7][8] = hide[2][7][9] = hide[2][7][10] = 1;
	hide[3][8][6] = hide[3][8][7] = 1;
	hide[3][9][6] = 1;
	hide[3][10][7] = 1;
	hide[3][12][2] = hide[3][12][3] = hide[3][12][4] = 1;
	hide[3][11][7] = 1;
	return 1;
}
int main() {
	//cin.tie(0)->sync_with_stdio(0);
	for (int i = 1; i <= 3; i++) if (i != 2) story_problem_exist[4][i] = 1;
	story_problem_exist[2][13] = 1;
	for (int i = 8; i <= 12; i++) story_selection_exist[3][i] = 1;
	story_selection_exist[1][1] = 1;
	for (int i = 1; i <= 3; i++) story_selection_exist[2][(1 << i) - 1] = 1;
	int stories_init_status = stories_init();
	if (stories_init_status == -1) {
		cout << "initialize failed\n";
	}
	else if (stories_init_status == 1) {
		//cout << "initialize complete\n";
		pair<int, int> STORY = {1, 1}, temp = STORY;
		while (STORY != make_pair(10, 10)) {
			temp = STORY, STORY = graph[STORY.f][STORY.s].run_story();
			story_visited[temp.f][temp.s] = true;
		}
	}
	else {
		cout << "unbeknown problem\n";
	}
	int n;
	cin >> n;
	return 0;
}
